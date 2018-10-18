FEATURE main.h/TearDown
this->tearEnvironmentClientsDown();

FEATURE main.h/Impl
private:
    std::vector<script::EnvironmentClient *> environmentClients;
    void tearEnvironmentClientsDown()
    {
        for (auto client : this->environmentClients)
        {
            delete client;
        }
        this->environmentClients.clear();
    }
