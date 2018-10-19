FEATURE main.h/Setup
this->setup_application_parameters();

FEATURE main.h/Impl
private:
    void setup_application_parameters()
    {
        MAIN_EXAMPLE_REGISTER_ENVIRONMENT_CLIENT(
            {
                "application.parameters"
            },
            this->process_application_parameters
        );
    }
    MAIN_EXAMPLE_ENVIRONMENT_FUNCTION(process_application_parameters)
    {
        std::vector<std::string> keysAndValues;
        for (auto parameter : this->parameters)
        {
            auto key = parameter.first;
            auto value = parameter.second;
            keysAndValues.push_back(key);
            keysAndValues.push_back(value);
        }
        return keysAndValues;
    }
