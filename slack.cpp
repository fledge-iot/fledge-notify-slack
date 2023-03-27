/*
 * Fledge "slack" notification delivery plugin.
 *
 * Copyright (c) 2019 Dianomic Systems
 *
 * Released under the Apache 2.0 Licence
 *
 * Author: Mark Riddoch           
 */
#include "slack.h"
#include <logger.h>
#include <simple_https.h>
#include <rapidjson/document.h>

using namespace std;
using namespace rapidjson;


/**
 * Construct a slack notification plugin
 *
 * @param category	The configuration of the plugin
 */
Slack::Slack(ConfigCategory *category)
{
	m_url = category->getValue("webhook");
	m_text = category->getValue("text");
}

/**
 * The destructure for the slack plugin
 */
Slack::~Slack()
{
}

/**
 * Send a notification via the Slack webhook
 *
 * @param notificationName 	The name of this notification
 * @param triggerReason		Why the notification is being sent
 * @param message		The message to send
 * @return bool			whether notify succeded or not
 */
bool Slack::notify(const string& notificationName, const string& triggerReason, const string& message)
{
	ostringstream   payload;
	SimpleHttps	*https = NULL;
	bool retVal = true;

	payload << "{ \"text\" : \"";
	payload << "*" << notificationName << "*\\n\\n";
	payload << message;
	Document doc;
	doc.Parse(triggerReason.c_str());
	if (!doc.HasParseError() && doc.HasMember("reason"))
	{
		payload << "Notification has " << doc["reason"].GetString() << "\\n";
	}
	payload << m_text << "\\n\\n";
	payload << "\" }";

	std::vector<std::pair<std::string, std::string>> headers;
	pair<string, string> header = make_pair("Content-type", "application/json");
	headers.push_back(header);

	if (m_url.empty())
	{
		Logger::getLogger()->error("Slack webhook is not set");
		return false;
	}

	/**
	 * Extract host and port from URL
	 */

	try
	{
		size_t findProtocol = m_url.find_first_of(":");
		string protocol = m_url.substr(0,findProtocol);
		
		string tmpUrl = m_url.substr(findProtocol + 3);
		size_t findPort = tmpUrl.find_first_of(":");
		size_t findPath = tmpUrl.find_first_of("/");
		string port, hostName;
		if (findPort == string::npos)
		{
			hostName = tmpUrl.substr(0, findPath);
			https  = new SimpleHttps(hostName);
		}
		else
		{
			hostName = tmpUrl.substr(0, findPort);
			port = tmpUrl.substr(findPort + 1 , findPath - findPort -1);
			string hostAndPort(hostName + ":" + port);
			https  = new SimpleHttps(hostAndPort);
		}

		int resCode = https->sendRequest("POST",
                                                    m_url,
                                                    headers,
                                                    payload.str());

                std::string strResCode = to_string(resCode);
                if(strResCode[0] != '2')
                {
                        Logger::getLogger()->error("Failed to send notification "
                                                   "to slack webhook  %s, resCode %d",
                                                   m_url.c_str(),
                                                   resCode);
                        retVal = false;
                }
	}
	catch (exception &e)
	{
		Logger::getLogger()->error("Exception while sending notification "
					   "to slack webhook  %s: %s",
					    m_url.c_str(),
					    e.what());
		retVal = false;

	}
	catch (...)
	{
		std::exception_ptr p = std::current_exception();
		string name = (p ? p.__cxa_exception_type()->name() : "null");

		Logger::getLogger()->error("Generic exception found while sending notification "
					   "to slack webhook  %s: %s",
					    m_url.c_str(),
					    name.c_str());

		retVal = false;
	}

	if (https)
	{
		delete https;
	}

	return retVal;
}

/**
 * Reconfigure the slack delivery plugin
 *
 * @param newConfig	The new configuration
 */
void Slack::reconfigure(const string& newConfig)
{
	ConfigCategory category("new", newConfig);
	m_url = category.getValue("webhook");
	m_text = category.getValue("text");
}
