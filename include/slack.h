#ifndef _SLACK_H
#define _SLACK_H
#include <config_category.h>
#include <string>
#include <logger.h>

/**
 * A simple slack notification class that sends a message
 * via a slack webhook URL
 */
class Slack {
	public:
		Slack(ConfigCategory *config);
		~Slack();
		bool	notify(const std::string& notificationName, const std::string& triggerReason, const std::string& message);
		void	reconfigure(const std::string& newConfig);
	private:
		std::string	m_url;
		std::string	m_text;
};
#endif
