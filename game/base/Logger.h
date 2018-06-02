#ifndef SHMUP_LOGGER_H
#define SHMUP_LOGGER_H

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define LOG(msg) \
    std::cout << "" << "[" << __FILENAME__  <<  __LINE__ << "]" << msg << std::endl

#endif //SHMUP_LOGGER_H
