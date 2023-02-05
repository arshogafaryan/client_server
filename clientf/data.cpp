#include "data.h"

void Data::set_data(const std::string& str) 
{
    std::unique_lock<std::mutex>lock(m_mx);
    m_str = str;
    m_data_cond.notify_one();
}

std::string Data::get_data() 
{
    std::unique_lock<std::mutex>ulock(m_mx);
    m_data_cond.wait(ulock);
    return m_str;
}
