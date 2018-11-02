FEATURE render.h/Impl
class MaterialPool
{
    public:
        MaterialPool() { }

        std::map<std::string, osg::ref_ptr<osg::StateSet> > materials;

        osg::StateSet *createMaterial(const std::string &name)
        {
            auto material = new osg::StateSet;
            this->materials[name] = material;
            return material;
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
