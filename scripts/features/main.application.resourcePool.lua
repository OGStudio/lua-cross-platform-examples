FEATURE main.lua/Impl
-- Crate resource pool.
main.application.resourcePool = {
    -- Report when loaded all requested resources.
    finishedLoading = core.createReporter(),
}

-- Configure resource pool.
do
    local pool = main.application.resourcePool
    -- Create environment client.
    local client = EnvironmentClient.new()
    -- Define finish keys.
    local finishKey = "application.resourcePool.finishedLoading"
    -- Define callback.
    client.call = function(key, values)
        if (key == finishKey)
        then
            pool.finishedLoading:report()
        end

        return {}
    end
    -- Register client.
    pool.client = client
    ENV:addClient(
        pool.client,
        {
            finishKey
        }
    );
end
