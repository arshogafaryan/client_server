#ifndef DATA_H
#define DATA_H
#include <condition_variable>

class Data 
{
public:
    Data():m_str(""){ }
    void set_data(const std::string& str);
    std::string get_data();

private:
    std::mutex m_mx;
    std::string m_str;
    std::condition_variable m_data_cond;
};

#endif