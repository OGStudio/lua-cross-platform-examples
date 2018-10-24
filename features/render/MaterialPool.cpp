FEATURE render.h/Impl
class MaterialPool
{
    public:
        MaterialPool() { }

        std::map<std::string, osg::ref_ptr<osg::StateSet> > materials;

        void createMaterial(const std::string &name)
        {
            this->materials[name] = new osg::StateSet;
        }

        osg::StateSet *material(const std::string &name)
        {
            auto it = this->materials.find(name);
            if (it != this->materials.end())
            {
                return it->second.get();
            }

            return 0;
        }

FEATURE render.h/End
};
