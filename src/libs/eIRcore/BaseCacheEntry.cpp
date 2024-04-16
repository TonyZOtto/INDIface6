#include "BaseCacheEntry.h"

BaseCacheEntry::BaseCacheEntry() : p_uid(Uid::BaseCacheEntry) {;}
BaseCacheEntry::BaseCacheEntry(const Key &key, const Id id)
    : p_uid(Uid::BaseCacheEntry), p_key(key), p_id(id) {;}

void BaseCacheEntry::set(const Key &key, const Id id)
{
    p_key = key, p_id = id;
}
