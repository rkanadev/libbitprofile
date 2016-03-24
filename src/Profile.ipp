namespace BitProfile{


template<class Callback>
void Profile::set(const std::string &key, const std::string &value, const Callback &callback)
{
    return executeConfirm
    (
        "set(string,string,string)", 
        CONTRACT_ARGUMENTS(key, value, ""),
        boost::bind(&Profile::checkKey, this, key, value),
        callback
    );
}


template<class Callback>
void Profile::clear(const std::string &key, const Callback &callback)
{
    return executeConfirm
    (
        "clear(string,string)", 
        CONTRACT_ARGUMENTS(key, ""),
        boost::bind(&Profile::checkKey, this, key, ""),
        callback
    );
}


template<class Callback>
void Profile::setPaymentAddress(const address_t &address, const Callback &callback)
{
    return set("payments", address, callback);
}


template<class Callback>
void Profile::transfer(const address_t &address, const Callback &callback)
{
    return executeConfirm
    (
        "transfer(address,string)",
        CONTRACT_ARGUMENTS(address, ""),
        boost::bind(&Profile::checkOwner, this, address),
        callback
    );
}


}