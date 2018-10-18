FEATURE main.h/Impl
#define MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(KEYS, FUNC) \
    auto client = new script::EnvironmentClient; \
    this->environment->addClient(client, KEYS); \
    client->call = SCRIPT_ENVIRONMENT_CLIENT_CALL(return FUNC(key,values);); \
    this->environmentClients.push_back(client);
