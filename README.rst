==========================================
Fledge slack notification delivery plugin
==========================================

A simple Slack notification delivery plugin.

The plugin uses the simple Slack webhook API to send notification
messages to a slack channel or individual user.

You must obtain a URL from Slack by visiting the page https://api.slack.com/apps

  - Select *Create New App*

  - Enter a name for your application, this must be unique for each Fledge slack application you create

  - Select your Slack workspace in which to deliver your notification. If not already logged in you may need to login to your workspace

  - Click on Create

  - Select *Incoming Webhooks*

  - Activate your webhook

  - Add your webhook to the workspace

  - Select the channel or individual to send the notification to

  - Authorize your webhook

  - Copy the Webhook URL into the plugin URL configuration item


You may also configure some static text that will be sent in each notification.

Installation
------------

The plugin can be installed with given `requirements.sh <requirements.sh>`_ or the following steps:


.. code-block:: bash

   $ sudo apt install -y libcurl4-openssl-dev


Build
-----
To build Fledge "slack notification" C++ plugin:

.. code-block:: console

  $ mkdir build
  $ cd build
  $ cmake ..
  $ make

- By default the Fledge develop package header files and libraries
  are expected to be located in /usr/include/fledge and /usr/lib/fledge
- If **FLEDGE_ROOT** env var is set and no -D options are set,
  the header files and libraries paths are pulled from the ones under the
  FLEDGE_ROOT directory.
  Please note that you must first run 'make' in the FLEDGE_ROOT directory.

You may also pass one or more of the following options to cmake to override 
this default behaviour:

- **FLEDGE_SRC** sets the path of a Fledge source tree
- **FLEDGE_INCLUDE** sets the path to Fledge header files
- **FLEDGE_LIB sets** the path to Fledge libraries
- **FLEDGE_INSTALL** sets the installation path of Random plugin

NOTE:
 - The **FLEDGE_INCLUDE** option should point to a location where all the Fledge 
   header files have been installed in a single directory.
 - The **FLEDGE_LIB** option should point to a location where all the Fledge
   libraries have been installed in a single directory.
 - 'make install' target is defined only when **FLEDGE_INSTALL** is set

Examples:

- no options

  $ cmake ..

- no options and FLEDGE_ROOT set

  $ export FLEDGE_ROOT=/some_fledge_setup

  $ cmake ..

- set FLEDGE_SRC

  $ cmake -DFLEDGE_SRC=/home/source/develop/Fledge  ..

- set FLEDGE_INCLUDE

  $ cmake -DFLEDGE_INCLUDE=/dev-package/include ..
- set FLEDGE_LIB

  $ cmake -DFLEDGE_LIB=/home/dev/package/lib ..
- set FLEDGE_INSTALL

  $ cmake -DFLEDGE_INSTALL=/home/source/develop/Fledge ..

  $ cmake -DFLEDGE_INSTALL=/usr/local/fledge ..
