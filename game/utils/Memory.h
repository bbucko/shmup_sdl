#ifndef SHMUP_MEMORY_H
#define SHMUP_MEMORY_H

#define DELETE_VECTOR(vector) \
    for(auto obj : vector) delete obj; vector.clear()

#define DELETE_MAP(map) \
    for(auto obj : map) delete obj.second; map.clear()


#endif //SHMUP_MEMORY_H
