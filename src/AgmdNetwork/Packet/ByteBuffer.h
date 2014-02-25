#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include <CommonDefines.h>

#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <stdlib.h>
#include <algorithm>

#define snprintf sprintf_s

namespace AgmdNetwork
{
    

    template<size_t T>
    inline void convert(char *val)
    {
        std::swap(*val, *(val + T - 1));
        convert<T - 2>(val + 1);
    }

    template<> inline void convert<0>(char *) {}
    template<> inline void convert<1>(char *) {}

    template<typename T> inline void apply(T *val)
    {
        convert<sizeof(T)>((char *)(val));
    }

    
    #define AGMD_BIGENDIAN 1
    #define AGMD_LITTLEENDIAN 0
    #define AGMD_ENDIAN AGMD_LITTLEENDIAN
    #if AGMD_ENDIAN == AGMD_BIGENDIAN
    template<typename T> inline void EndianConvert(T& val) { apply<T>(&val); }
    template<typename T> inline void EndianConvertReverse(T&) { }
    #else
    template<typename T> inline void EndianConvert(T&) { }
    template<typename T> inline void EndianConvertReverse(T& val) { apply<T>(&val); }
    #endif

    template<typename T> void EndianConvert(T*);
    template<typename T> void EndianConvertReverse(T*);

    inline void EndianConvert(a_uint8&) { }
    inline void EndianConvert( a_int8&) { }
    inline void EndianConvertReverse(a_uint8&) { }
    inline void EndianConvertReverse( a_int8&) { }

    class ByteBufferException
    {
        public:
            ByteBufferException(size_t pos, size_t size, size_t valueSize)
                : Pos(pos), Size(size), ValueSize(valueSize)
            {
            }

        protected:
            size_t Pos;
            size_t Size;
            size_t ValueSize;
    };

    class ByteBufferPositionException : public ByteBufferException
    {
        public:
            ByteBufferPositionException(bool add, size_t pos, size_t size, size_t valueSize)
            : ByteBufferException(pos, size, valueSize), _add(add)
            {
                PrintError();
            }

        protected:
            void PrintError() const
            {

            }

        private:
            bool _add;
    };

    class ByteBufferSourceException : public ByteBufferException
    {
        public:
            ByteBufferSourceException(size_t pos, size_t size, size_t valueSize)
            : ByteBufferException(pos, size, valueSize)
            {
                PrintError();
            }

        protected:
            void PrintError() const
            {
            }
    };


    class ByteBuffer
    {
        public:
            const static size_t DEFAULT_SIZE = 0x1000;

            ByteBuffer(): _rpos(0), _wpos(0)
            {
                _storage.reserve(DEFAULT_SIZE);
            }

            ByteBuffer(size_t res): _rpos(0), _wpos(0)
            {
                _storage.reserve(res);
            }

            ByteBuffer(const ByteBuffer &buf): _rpos(buf._rpos), _wpos(buf._wpos), _storage(buf._storage) { }

            void clear()
            {
                _storage.clear();
                _rpos = _wpos = 0;
            }

            template <typename T> void append(T value)
            {
                EndianConvert(value);
                append((a_uint8 *)&value, sizeof(value));
            }

            template <typename T> void put(size_t pos, T value)
            {
                EndianConvert(value);
                put(pos, (a_uint8 *)&value, sizeof(value));
            }

            ByteBuffer &operator<<(a_uint8 value)
            {
                append<a_uint8>(value);
                return *this;
            }

            ByteBuffer &operator<<(a_uint16 value)
            {
                append<a_uint16>(value);
                return *this;
            }

            ByteBuffer &operator<<(a_uint32 value)
            {
                append<a_uint32>(value);
                return *this;
            }

            ByteBuffer &operator<<(a_uint64 value)
            {
                append<a_uint64>(value);
                return *this;
            }

            ByteBuffer &operator<<(a_int8 value)
            {
                append<a_int8>(value);
                return *this;
            }

            ByteBuffer &operator<<(a_int16 value)
            {
                append<a_int16>(value);
                return *this;
            }

            ByteBuffer &operator<<(a_int32 value)
            {
                append<a_int32>(value);
                return *this;
            }

            ByteBuffer &operator<<(a_int64 value)
            {
                append<a_int64>(value);
                return *this;
            }

            ByteBuffer &operator<<(float value)
            {
                append<float>(value);
                return *this;
            }

            ByteBuffer &operator<<(double value)
            {
                append<double>(value);
                return *this;
            }

            ByteBuffer &operator<<(const std::string &value)
            {
                if (size_t len = value.length())
                    append((a_uint8 const*)value.c_str(), len);
                append((a_uint8)0);
                return *this;
            }

            ByteBuffer &operator<<(const char *str)
            {
                if (size_t len = (str ? strlen(str) : 0))
                    append((a_uint8 const*)str, len);
                append((a_uint8)0);
                return *this;
            }

            ByteBuffer &operator>>(bool &value)
            {
                value = read<char>() > 0 ? true : false;
                return *this;
            }

            ByteBuffer &operator>>(a_uint8 &value)
            {
                value = read<a_uint8>();
                return *this;
            }

            ByteBuffer &operator>>(a_uint16 &value)
            {
                value = read<a_uint16>();
                return *this;
            }

            ByteBuffer &operator>>(a_uint32 &value)
            {
                value = read<a_uint32>();
                return *this;
            }

            ByteBuffer &operator>>(a_uint64 &value)
            {
                value = read<a_uint64>();
                return *this;
            }

            ByteBuffer &operator>>(a_int8 &value)
            {
                value = read<a_int8>();
                return *this;
            }

            ByteBuffer &operator>>(a_int16 &value)
            {
                value = read<a_int16>();
                return *this;
            }

            ByteBuffer &operator>>(a_int32 &value)
            {
                value = read<a_int32>();
                return *this;
            }

            ByteBuffer &operator>>(a_int64 &value)
            {
                value = read<a_int64>();
                return *this;
            }

            ByteBuffer &operator>>(float &value)
            {
                value = read<float>();
                return *this;
            }

            ByteBuffer &operator>>(double &value)
            {
                value = read<double>();
                return *this;
            }

            ByteBuffer &operator>>(std::string& value)
            {
                value.clear();
                while (rpos() < size())
                {
                    char c = read<char>();
                    if (c == 0)
                        break;
                    value += c;
                }
                return *this;
            }

            a_uint8 operator[](size_t pos) const
            {
                return read<a_uint8>(pos);
            }

            size_t rpos() const { return _rpos; }

            size_t rpos(size_t rpos_)
            {
                _rpos = rpos_;
                return _rpos;
            }

            void rfinish()
            {
                _rpos = wpos();
            }

            size_t wpos() const { return _wpos; }

            size_t wpos(size_t wpos_)
            {
                _wpos = wpos_;
                return _wpos;
            }

            template<typename T>
            void read_skip() { read_skip(sizeof(T)); }

            void read_skip(size_t skip)
            {
                if (_rpos + skip > size())
                    throw ByteBufferPositionException(false, _rpos, skip, size());
                _rpos += skip;
            }

            template <typename T> T read()
            {
                T r = read<T>(_rpos);
                _rpos += sizeof(T);
                return r;
            }

            template <typename T> T read(size_t pos) const
            {
                if (pos + sizeof(T) > size())
                    throw ByteBufferPositionException(false, pos, sizeof(T), size());
                T val = *((T const*)&_storage[pos]);
                EndianConvert(val);
                return val;
            }

            void read(a_uint8 *dest, size_t len)
            {
                if (_rpos  + len > size())
                   throw ByteBufferPositionException(false, _rpos, len, size());
                memcpy(dest, &_storage[_rpos], len);
                _rpos += len;
            }

            void readPackGUID(a_uint64& guid)
            {
                if (rpos() + 1 > size())
                    throw ByteBufferPositionException(false, _rpos, 1, size());

                guid = 0;

                a_uint8 guidmark = 0;
                (*this) >> guidmark;

                for (int i = 0; i < 8; ++i)
                {
                    if (guidmark & (a_uint8(1) << i))
                    {
                        if (rpos() + 1 > size())
                            throw ByteBufferPositionException(false, _rpos, 1, size());

                        a_uint8 bit;
                        (*this) >> bit;
                        guid |= (a_uint64(bit) << (i * 8));
                    }
                }
            }

            const a_uint8 *contents() const { return &_storage[0]; }

            size_t size() const { return _storage.size(); }
            bool empty() const { return _storage.empty(); }

            void resize(size_t newsize)
            {
                _storage.resize(newsize, 0);
                _rpos = 0;
                _wpos = size();
            }

            void reserve(size_t ressize)
            {
                if (ressize > size())
                    _storage.reserve(ressize);
            }

            void append(const char *src, size_t cnt)
            {
                return append((const a_uint8 *)src, cnt);
            }

            template<class T> void append(const T *src, size_t cnt)
            {
                return append((const a_uint8 *)src, cnt * sizeof(T));
            }

            void append(const a_uint8 *src, size_t cnt)
            {
                if (!cnt)
                    throw ByteBufferSourceException(_wpos, size(), cnt);

                if (!src)
                    throw ByteBufferSourceException(_wpos, size(), cnt);

                //ASSERT(size() < 10000000);

                if (_storage.size() < _wpos + cnt)
                    _storage.resize(_wpos + cnt);
                memcpy(&_storage[_wpos], src, cnt);
                _wpos += cnt;
            }

            void append(const ByteBuffer& buffer)
            {
                if (buffer.wpos())
                    append(buffer.contents(), buffer.wpos());
            }

            void appendPackXYZ(float x, float y, float z)
            {
                a_uint32 packed = 0;
                packed |= ((int)(x / 0.25f) & 0x7FF);
                packed |= ((int)(y / 0.25f) & 0x7FF) << 11;
                packed |= ((int)(z / 0.25f) & 0x3FF) << 22;
                *this << packed;
            }

            void appendPackGUID(a_uint64 guid)
            {
                a_uint8 packGUID[8+1];
                packGUID[0] = 0;
                size_t size = 1;
                for (a_uint8 i = 0;guid != 0;++i)
                {
                    if (guid & 0xFF)
                    {
                        packGUID[0] |= a_uint8(1 << i);
                        packGUID[size] =  a_uint8(guid & 0xFF);
                        ++size;
                    }

                    guid >>= 8;
                }
                append(packGUID, size);
            }

            void put(size_t pos, const a_uint8 *src, size_t cnt)
            {
                if (pos + cnt > size())
                    throw ByteBufferPositionException(true, pos, cnt, size());

                if (!src)
                    throw ByteBufferSourceException(_wpos, size(), cnt);

                memcpy(&_storage[pos], src, cnt);
            }

            void print_storage() const
            {

                std::ostringstream o;
                o << "STORAGE_SIZE: " << size();
                for (a_uint32 i = 0; i < size(); ++i)
                    o << read<a_uint8>(i) << " - ";
                o << " ";

            }

            void textlike() const
            {

                std::ostringstream o;
                o << "STORAGE_SIZE: " << size();
                for (a_uint32 i = 0; i < size(); ++i)
                {
                    char buf[1];
                    
                    snprintf(buf, 1, "%c", read<a_uint8>(i));
                    o << buf;
                }
                o << " ";
            }

            void hexlike() const
            {
                a_uint32 j = 1, k = 1;

                std::ostringstream o;
                o << "STORAGE_SIZE: " << size();

                for (a_uint32 i = 0; i < size(); ++i)
                {
                    char buf[3];
                    snprintf(buf, 1, "%2X ", read<a_uint8>(i));
                    if ((i == (j * 8)) && ((i != (k * 16))))
                    {
                        o << "| ";
                        ++j;
                    }
                    else if (i == (k * 16))
                    {
                        o << "\n";
                        ++k;
                        ++j;
                    }

                    o << buf;
                }
                o << " ";
            }

        protected:
            size_t _rpos, _wpos;
            std::vector<a_uint8> _storage;
    };

    template <typename T>
    inline ByteBuffer &operator<<(ByteBuffer &b, std::vector<T> v)
    {
        b << (a_uint32)v.size();
        for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
        {
            b << *i;
        }
        return b;
    }

    template <typename T>
    inline ByteBuffer &operator>>(ByteBuffer &b, std::vector<T> &v)
    {
        a_uint32 vsize;
        b >> vsize;
        v.clear();
        while (vsize--)
        {
            T t;
            b >> t;
            v.push_back(t);
        }
        return b;
    }

    template <typename T>
    inline ByteBuffer &operator<<(ByteBuffer &b, std::list<T> v)
    {
        b << (a_uint32)v.size();
        for (typename std::list<T>::iterator i = v.begin(); i != v.end(); ++i)
        {
            b << *i;
        }
        return b;
    }

    template <typename T>
    inline ByteBuffer &operator>>(ByteBuffer &b, std::list<T> &v)
    {
        a_uint32 vsize;
        b >> vsize;
        v.clear();
        while (vsize--)
        {
            T t;
            b >> t;
            v.push_back(t);
        }
        return b;
    }

    template <typename K, typename V>
    inline ByteBuffer &operator<<(ByteBuffer &b, std::map<K, V> &m)
    {
        b << (a_uint32)m.size();
        for (typename std::map<K, V>::iterator i = m.begin(); i != m.end(); ++i)
        {
            b << i->first << i->second;
        }
        return b;
    }

    template <typename K, typename V>
    inline ByteBuffer &operator>>(ByteBuffer &b, std::map<K, V> &m)
    {
        a_uint32 msize;
        b >> msize;
        m.clear();
        while (msize--)
        {
            K k;
            V v;
            b >> k >> v;
            m.insert(make_pair(k, v));
        }
        return b;
    }

    template<> inline std::string ByteBuffer::read<std::string>()
    {
        std::string tmp;
        *this >> tmp;
        return tmp;
    }

    template<>
    inline void ByteBuffer::read_skip<char*>()
    {
        std::string temp;
        *this >> temp;
    }

    template<>
    inline void ByteBuffer::read_skip<char const*>()
    {
        read_skip<char*>();
    }

    template<>
    inline void ByteBuffer::read_skip<std::string>()
    {
        read_skip<char*>();
    }
}

#endif /*BYTEBUFFER_H*/