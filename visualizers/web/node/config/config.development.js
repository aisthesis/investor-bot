var config = {};
config.web = {};

config.web.host = process.env.OPTBOT_UI_HOST || '127.0.0.1';
config.web.port = process.env.OPTBOT_UI_PORT || 8080;

module.exports = config;