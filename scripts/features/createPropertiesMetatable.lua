FEATURE main.lua/Impl
function createPropertiesMetatable()
    local mt =
    {
        -- Register properties with callbacks.
        callbacks = {},
        register = function(mtself, key, getter, setter)
            local callback = {}
            callback.getter = getter
            callback.setter = setter
            mtself.callbacks[key] = callback
        end,

        -- Getter.
        __index = function(self, key)
            local mtself = getmetatable(self)
            local callback = mtself.callbacks[key]
            if 
                callback and
                callback.getter
            then
                return callback.getter()
            end
            return nil
        end,

        -- Setter.
        __newindex = function(self, key, value)
            local mtself = getmetatable(self)
            local callback = mtself.callbacks[key]
            if 
                callback and
                callback.setter
            then
                callback.setter(value)
            end
        end,
    }
    return mt
end
