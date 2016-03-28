namespace BitProfile{



class KeyAdapter::KeyHolder
{
    public:
        virtual const address_t & getAddress() const = 0;
        virtual std::pair<bool, std::string> authenticate(Provider &, const std::string &password) = 0;
};


template<class Key>
class KeyAdapter::KeyHolderImpl : public KeyAdapter::KeyHolder
{
    public:
        KeyHolderImpl(const Key &);

        const address_t & getAddress() const;
        std::pair<bool, std::string> authenticate(Provider &, const std::string &password);

    private:
        Key _key;
};


template<class Key>
KeyAdapter::KeyHolderImpl<Key>::KeyHolderImpl(const Key &key) :
    _key(key)
{}


template<class Key>
const address_t & KeyAdapter::KeyHolderImpl<Key>::getAddress() const
{
    return _key.getAddress();
}


template<class Key>
std::pair<bool, std::string> KeyAdapter::KeyHolderImpl<Key>::authenticate(Provider &provider, const std::string &password)
{
    return _key.authenticate(provider, password);
}


template<class Key>
KeyAdapter::KeyAdapter(const Key &key) :
    _holder(new KeyHolderImpl<Key>(key))
{}

template<class Key>
void KeyAdapter::reset(const Key &key)
{
    _holder.reset(new KeyHolderImpl<Key>(key));
}


template<class Key>
void KeyAdapter::operator = (const Key &key)
{
    _holder.reset(new KeyHolderImpl<Key>(key));
}





}