/****************************************************************************
* Author:   Lukaß Zhang
* Since:    2023/05/31
* Modifyed: 2023/08/23
* Email:    sunny_clouds@outlook.com
* 
* Please forgive me for leaving a long paragraph of text written to let my
* annoyance out for lacking a visual tool to show what the STL containers
* contain while debugging and learning algorithm. I always need to set
* breakpoints manually, move my mouse onto the variables and wait for a
* small tip box to show up with folded information. Accordingly, I coded
* this and named it as 'preinte', which is the origin of the word 'print'
* from old French. I hope my commitment could also help you to debug while
* learning or working. Wish you happy coding. :)
* 
* Actually, I worked out a version for C first, and this version for C++ was
* based on that. However, that C version was too crude to use, so I almost
* overwrote all code inherited from that old version. Even though I uploaded
* the C version, I do not recommend you to use that. Please use this version
* with C++ compiler if possible.
* 
* This version can be compiled by MSVC, GCC or Clang. (>=C++14)
* 
* Copyright 2023 Lekco. All Rights Reserved.
****************************************************************************/

#ifndef __cplusplus
#error C++ compiler required.
#else
#ifndef _PREINTE_
#define _PREINTE_

#include <iostream>
#include <sstream>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ctime>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <cstring>
#include <string>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <array>

namespace preinte {

    // Here comes the slope of fundamental code.

#define STD ::std

    // The struct verifys whether the decayed _Ty1 is same as _Ty2.
    template <typename _Ty1, typename _Ty2>
    struct is_decayed_same
        : STD::is_same<typename STD::decay<_Ty1>::type, _Ty2>::type {
    };

    // The varification of struct is_decayed_same.
    template <typename _Ty1, typename _Ty2>
    constexpr bool is_decayed_same_v = is_decayed_same<_Ty1, _Ty2>::value;

    // The check struct for _Ty that doesn't have operator<<(std::ostream&).
    template <typename _Ty, typename = void>
    struct has_operator_insertion_check
        : STD::false_type {
    };

    // The check struct for _Ty having operator<<(std::ostream&).
    template <typename _Ty>
    struct has_operator_insertion_check<_Ty, STD::void_t<decltype((STD::declval<STD::ostream&>() << STD::declval<_Ty>()))>>
        : STD::true_type {
    };

    // The varification of struct has_operator_insertion_check.
    template <typename _Ty>
    constexpr bool has_operator_insertion_v = has_operator_insertion_check<_Ty>::value;

    // The check struct for object that doesn't pass the operator insertion check.
    template <typename _Ty, typename = void>
    struct is_printable_check
        : STD::false_type {
    };

    // The check struct for object that pass the operator insertion check.
    template <typename _Ty>
    struct is_printable_check<_Ty, typename STD::enable_if_t<has_operator_insertion_v<_Ty>>>
        : STD::true_type {
    };
    
    // The varification of struct is_printable_check.
    template <typename _Ty>
    constexpr bool is_printable_v = is_printable_check<_Ty>::value;

    // The return type of operator insertion check for _Ty.
    template <typename _Ty, typename _Ret = void>
    using is_printable_t = typename STD::enable_if_t<has_operator_insertion_v<_Ty>, _Ret>;

    // The return type of operator insertion check for both _Ty1 and _Ty2.
    template <typename _Ty1, typename _Ty2, typename _Ret = void>
    using are_printable_t = typename STD::enable_if_t<has_operator_insertion_v<_Ty1> && has_operator_insertion_v<_Ty2>, _Ret>;

    // The check struct for object that isn't built-in.
    template <typename _Ty, typename = void>
    struct is_built_in_check
        : STD::false_type {
    };

    // The check struct for object that is built-in.
    template <typename _Ty>
    struct is_built_in_check<_Ty, typename STD::enable_if_t<
        is_decayed_same_v<_Ty, int> ||
        is_decayed_same_v<_Ty, unsigned int> ||
        is_decayed_same_v<_Ty, short> ||
        is_decayed_same_v<_Ty, unsigned short> ||
        is_decayed_same_v<_Ty, float> ||
        is_decayed_same_v<_Ty, double> ||
        is_decayed_same_v<_Ty, long> ||
        is_decayed_same_v<_Ty, unsigned long> ||
        is_decayed_same_v<_Ty, long long> ||
        is_decayed_same_v<_Ty, unsigned long long> ||
        is_decayed_same_v<_Ty, long double> ||
        is_decayed_same_v<_Ty, char*> ||
        is_decayed_same_v<_Ty, STD::string> ||
        is_decayed_same_v<_Ty, bool>>>
        : STD::true_type {
    };

    // The varification of struct is_built_in_check.
    template <typename _Ty>
    constexpr bool is_built_in_v = is_built_in_check<_Ty>::value;

    // The contrary varification of struct is_built_in_check.
    template <typename _Ty>
    constexpr bool is_not_built_in_v = !is_built_in_v<_Ty>;

    // The return type of built-in check for _Ty.
    template <typename _Ty, typename _Ret = void>
    using is_built_in_t = typename STD::enable_if_t<is_built_in_v<_Ty>, _Ret>;

    // The return type of built-in check for _BTy and printable check for _PTy.
    template <typename _Bty, typename _Pty, typename _Ret = void>
    using partly_built_in = typename STD::enable_if_t<is_built_in_v<_Bty> && is_printable_v<_Pty>, _Ret>;

    // The return type of built-in check for _Ty1 and _Ty2.
    template <typename _Ty1, typename _Ty2, typename _Ret = void>
    using are_built_in_t = typename STD::enable_if_t<is_built_in_v<_Ty1> && is_built_in_v<_Ty2>, _Ret>;

    // A helper class for printing string.
    class str_tool {
    public:
        // Get the width of an unsigned long long number.
        static size_t as_string_len(const size_t& _Content) {
            size_t disposed = _Content / 10, width = 1;
            while (disposed) {
                width++;
                disposed /= 10;
            }
            return width;
        }

        // Get the width of string converted from _Ty.
        template <typename _Ty>
        static is_printable_t<_Ty, size_t> as_string_len(const _Ty& _Val) {
            STD::stringstream ss;
            ss << _Val;
            return ss.str().size();
        }

        // Get the width of C-style string.
        inline static size_t as_string_len(const char* _Str) {
            return strlen(_Str);
        }

        // Get the width of std::string.
        inline static size_t as_string_len(const STD::string& _Str) {
            return _Str.size();
        }

        // Get a content-duplicated std::string.
        template <typename _Ty>
        static is_printable_t<_Ty, STD::string> duplicate(const _Ty& _Content, size_t _Times) {
            STD::stringstream ss;
            while (_Times--) {
                ss << _Content;
            }
            return ss.str();
        }

        // Get a content-centered std::string.
        template <typename _Ty>
        static is_printable_t<_Ty, STD::string> center(const _Ty& _Content, const size_t& _Width, const bool& _Align_Left) {
            size_t width = as_string_len(_Content);
            STD::stringstream ss;
            if (_Width < width) {
                ss << _Content;
                return ss.str().substr(0, _Width);
            }
            size_t left = (_Width - width) / 2;
            if (!(_Width % 2 && width % 2 || !(_Width % 2) && !(width % 2))) {
                left += _Align_Left ? 0 : 1;
            }
            ss << duplicate(' ', left) << _Content << duplicate(' ', _Width - width - left);
            return ss.str();
        }

        // Concat the given elements into std::string.
        template <typename... _Tys>
        static STD::string concat(_Tys&&... _Contents) {
            STD::stringstream ss;
            const int program[] = { 0, (ss << STD::forward<_Tys>(_Contents), 0)... };
            static_cast<void>(program);
            return ss.str();
        }
    };

#define STT str_tool

    // The format for print.
    struct print_format {
        // The alignment of print format.
        enum class ALIGNMENT {
            LEFT, CENTER, RIGHT
        };

        const char* name;      // The type's name.
        size_t      width;     // The width of cell when printing into cells.
        size_t      length;    // The column length of cells.
        size_t      digits;    // The decimal digits for numeric types.
        ALIGNMENT   alignment; // Whether the value is aligned to the left when printing into cells.

        // Construct an instance of struct print_format.
        print_format(const char* _Name, const size_t& _Width, const size_t& _Length, const size_t& _Digits = 0, ALIGNMENT _Align = ALIGNMENT::LEFT)
            : name(_Name)
            , width(_Width)
            , length(_Length)
            , digits(_Digits)
            , alignment(_Align) {
        }

        // Construct an instance of struct print_format.
        print_format()
            : name("<unnamed type>")
            , width(7)
            , length(5)
            , digits(0)
            , alignment(ALIGNMENT::LEFT) {
        }

        // Print the value in a line with given format.
        template <typename _Ty>
        is_printable_t<_Ty> print_inline(const _Ty& _Val) const {
            STD::cout << STD::left << STD::fixed << STD::setprecision(digits) << _Val;
        }

        // Print the value in a cell with given format.
        template <typename _Ty>
        is_printable_t<_Ty> print_incell(const _Ty& _Val) const {
            STD::cout << STD::fixed << STD::setprecision(digits);
            if (alignment == ALIGNMENT::CENTER) {
                STD::cout << STT::center(_Val, width, true);
            }
            else {
                STD::cout << (alignment == ALIGNMENT::LEFT ? STD::left : STD::right) << STD::setw(width) << _Val;
            }
        }
    };

    // A helper class for printing.
    class print_tool {
    public:
        // The maximum of the table's rows.
        static size_t _Max_rows;

        // The stream buffer targeting to console.
        static STD::streambuf* _Stream_cns;

        // Here are print_formats for all built-in types.
        static print_format _Format_d,   _Format_u, _Format_hd, _Format_uhd, _Format_f, _Format_ld;
        static print_format _Format_uld, _Format_cs, _Format_lf, _Format_lld, _Format_zd, _Format_Lf;
        static print_format _Format_s,   _Format_b;

        // Turn to a new line.
        static constexpr char NEW_LINE = '\n';

        // Get current time and formated it as std::string.
        static STD::string now() {
            time_t now = time(nullptr);
            struct tm* plocaltime = localtime(&now);
            char now_s[24] = { 0 };
            sprintf(now_s, "%04d/%02d/%02d %d:%02d:%02d", plocaltime->tm_year + 1900, plocaltime->tm_mon + 1,
                plocaltime->tm_mday, plocaltime->tm_hour, plocaltime->tm_min, plocaltime->tm_sec);
            return now_s;
        }

        // Turn the std::cout to file stream.
        static void to_file(const STD::ofstream& _File_Stream) {
            if (!_File_Stream.is_open()) {
                throw STD::runtime_error("File is not open.\n");
                return;
            }
            STD::cout.rdbuf(_File_Stream.rdbuf());
        }

        // Turn the std::cout to the console.
        inline static void to_console() {
            STD::cout.rdbuf(_Stream_cns);
        }

        // Print a tip into the console and pause the program by waiting for keyboard input.
        static void pause(const std::string& _Tip = "") {
            STD::cout << STT::duplicate('*', 80) << NEW_LINE;
            if (_Tip.size() > 0) {
                STD::cout << '[' << now() << ']' << ' ' << _Tip << NEW_LINE;
            }
            printf("[%s] Program is paused. Please press 'Enter' to continue.", now().c_str());
            while (getchar() != '\n');
            STD::cout << STT::duplicate('*', 80) << NEW_LINE;
        }

        // To round up the value of a devides b.
        inline static size_t ceil_divide(const size_t& a, const size_t& b) {
            return a / b + ((a % b > 0) ? 1 : 0);
        }

        // Print one-template type's tip.
        template <typename _Ty>
        static void tip(const _Ty& _Obj, const char* _Obj_Ty_Name, const char* _Ty_Name, const char* _Obj_Name, const size_t& _Len) {
            STD::cout << '@' << (void*)(&_Obj) << ' ' << _Obj_Ty_Name << '<' << _Ty_Name << "> " << _Obj_Name << "[.size() = " << _Len << "]:\n";
        }

        // Print two-template type's tip.
        template <typename _Ty>
        static void tip(const _Ty& _Obj, const char* _Obj_Ty_Name, const char* _Kty_Name, const char* _Vty_Name, const char* _Obj_Name, const size_t& _Len) {
            STD::cout << '@' << (void*)(&_Obj) << ' ' << _Obj_Ty_Name << '<' << _Kty_Name << ", " << _Vty_Name << "> " << _Obj_Name << "[.size() = " << _Len << "]:\n";
        }

        // Print an id or a range of id into a cell.
        static void print_id(const size_t& _Start, const size_t& _End, const size_t& _Width);

        // Set the width of a built-in type.
        template <typename _Ty>
        static is_built_in_t<_Ty> set_width(const size_t& _Width);

        // Set the length of a built-in type.
        template <typename _Ty>
        static is_built_in_t<_Ty> set_length(const size_t& _Length);

        // Set the digits of a built-in type.
        template <typename _Ty>
        static is_built_in_t<_Ty> set_digits(const size_t& _Digit);

        // Set the alignment of a built-in type.
        template <typename _Ty>
        static is_built_in_t<_Ty> set_alignment(const print_format::ALIGNMENT& _Align);
    };

#define PRT print_tool

    size_t          PRT::_Max_rows   = -1;
    STD::streambuf* PRT::_Stream_cns = STD::cout.rdbuf();

#define _SET_BUILT_IN_FORMAT(_NAME_, _TYPE_, _WIDTH_, _LENGTH_, _DIGITS_, _ALIGN_) \
    print_format PRT::_NAME_ { #_TYPE_, _WIDTH_, _LENGTH_, _DIGITS_, print_format::ALIGNMENT::_ALIGN_ }
   
    _SET_BUILT_IN_FORMAT(_Format_d,   int,                7,  10, 0, RIGHT);
    _SET_BUILT_IN_FORMAT(_Format_u,   unsigned int,       7,  10, 0, RIGHT);
    _SET_BUILT_IN_FORMAT(_Format_hd,  short,              6,  10, 0, RIGHT);
    _SET_BUILT_IN_FORMAT(_Format_uhd, unsigned short,     6,  10, 0, RIGHT);
    _SET_BUILT_IN_FORMAT(_Format_f,   float,              9,  10, 2, RIGHT);
    _SET_BUILT_IN_FORMAT(_Format_ld,  long,               10, 10, 0, RIGHT);
    _SET_BUILT_IN_FORMAT(_Format_uld, unsigned long,      10, 10, 0, RIGHT);
    _SET_BUILT_IN_FORMAT(_Format_cs,  char,               80, 1,  0, LEFT );
    _SET_BUILT_IN_FORMAT(_Format_lf,  double,             10, 10, 2, RIGHT);
    _SET_BUILT_IN_FORMAT(_Format_lld, long long,          10, 10, 0, RIGHT);
    _SET_BUILT_IN_FORMAT(_Format_zd,  unsigned long long, 10, 10, 0, RIGHT);
    _SET_BUILT_IN_FORMAT(_Format_Lf,  long double,        10, 10, 2, RIGHT);
    _SET_BUILT_IN_FORMAT(_Format_b,   bool,               3,  25, 0, RIGHT);
    _SET_BUILT_IN_FORMAT(_Format_s,   STD::string,        80, 1,  0, LEFT );

#undef _SET_BUILT_IN_FORMAT

    // Get the print_format of built-in types with given type.
    template <typename _Ty>
    static print_format& get_built_in_format() {
        static_assert(true, "The type of given parameter is not built in.");
        throw;
    }

#define _GET_BUILT_IN_FORMAT(_TYPE_, _FORMAT_) \
    template <> inline print_format& get_built_in_format<_TYPE_>() { return print_tool::_FORMAT_; }

    _GET_BUILT_IN_FORMAT(int,                _Format_d  )
    _GET_BUILT_IN_FORMAT(unsigned int,       _Format_u  )
    _GET_BUILT_IN_FORMAT(short,              _Format_hd )
    _GET_BUILT_IN_FORMAT(unsigned short,     _Format_uhd)
    _GET_BUILT_IN_FORMAT(float,              _Format_f  )
    _GET_BUILT_IN_FORMAT(long,               _Format_ld )
    _GET_BUILT_IN_FORMAT(unsigned long,      _Format_uld)
    _GET_BUILT_IN_FORMAT(char*,              _Format_cs )
    _GET_BUILT_IN_FORMAT(double,             _Format_lf )
    _GET_BUILT_IN_FORMAT(long long,          _Format_lld)
    _GET_BUILT_IN_FORMAT(unsigned long long, _Format_zd )
    _GET_BUILT_IN_FORMAT(long double,        _Format_Lf )
    _GET_BUILT_IN_FORMAT(bool,               _Format_b  )
    _GET_BUILT_IN_FORMAT(STD::string,        _Format_s  )

#undef _GET_BUILT_IN_FORMAT

    // Set the width of a built-in type.
    template <typename _Ty>
    is_built_in_t<_Ty> print_tool::set_width(const size_t& _Width) {
        if (_Width > 0) {
            get_built_in_format<_Ty>().width = _Width;
        }
    }

    // Set the length of a built-in type.
    template <typename _Ty>
    is_built_in_t<_Ty> PRT::set_length(const size_t& _Length) {
        if (_Length > 0) {
            get_built_in_format<_Ty>().length = _Length;
        }
    }

    // Set the digits of a built-in type.
    template <typename _Ty>
    is_built_in_t<_Ty> PRT::set_digits(const size_t& _Digit) {
        get_built_in_format<_Ty>().digits = _Digit;
    }

    // Set the alignment of a built-in type.
    template <typename _Ty>
    is_built_in_t<_Ty> PRT::set_alignment(const print_format::ALIGNMENT& _Align) {
        get_built_in_format<_Ty>().alignment = _Align;
    }

    // The format for linked-list's print.
    template <typename _Node_Ty, typename _Data_Ty, typename = is_printable_t<_Data_Ty>>
    struct linked_node_format {
        const char*  node_name;	// The name of node.
        print_format format;    // The print format of node's data.
        STD::function<_Data_Ty& (_Node_Ty*)> data_func; // The function to get the data by given node.
        STD::function<_Node_Ty* (_Node_Ty*)> next_func; // The function to get the next node by given node.

        // Construct an instance of linked-list's print whose data is built-in.
        linked_node_format(const char* _Node_Name, const print_format& _Format, const STD::function<_Data_Ty& (_Node_Ty*)>& _Data_Func, const STD::function<_Node_Ty* (_Node_Ty*)>& _Next_Func)
            : node_name(_Node_Name)
            , format(_Format)
            , data_func(_Data_Func)
            , next_func(_Next_Func) {
        }

        // Construct an instance of linked-list's print whose data isn't built-in.
        linked_node_format(const char* _Node_Name, const STD::function<_Data_Ty& (_Node_Ty*)>& _Data_Func, STD::function<_Node_Ty* (_Node_Ty*)> _Next_Func)
            : node_name(_Node_Name)
            , format(get_built_in_format<_Data_Ty>())
            , data_func(_Data_Func)
            , next_func(_Next_Func) {
        }

        // Get the data by the point to the node.
        inline _Data_Ty& get_data(_Node_Ty* const _Ptr) const {
            return data_func(_Ptr);
        }

        // Get the next node by the point to the node.
        inline _Node_Ty* get_next(_Node_Ty* const _Ptr) const {
            return next_func(_Ptr);
        }
    };

    // An access-limited array whose size is given and of memory-safe.
    template <typename _Ty>
    class limited_array {
    protected:
        static STD::allocator<_Ty> _alloc;  // The allocator of _Ty.
        size_t                     _size;	// The size of the array.
        _Ty*				       _data;	// The head pointer of data.
        mutable _Ty*               _ptr;    // The sequential pointer of the array.

        // Destory all data in the array.
        void tidy() const {
            for (_Ty* p = _data; p < _data + _size; p++) {
                p->~_Ty();
            }
        }

        // Check the given pointer whether is in range.
        inline bool check(_Ty* const _Ptr) const {
            return _Ptr >= _data && _Ptr < _data + _size;
        }

        // Throw an error when pointer is out of range.
        inline void out_range() const {
            throw STD::runtime_error("Index is out of range.");
        }

    public:
        // The value type of the array.
        using value_type = _Ty;

        // Copy an existing array.
        limited_array(const limited_array& _Copy)
            : _size(_Copy.size())
            , _data(_alloc.allocate(_size))
            , _ptr(_data) {
            STD::memcpy(_data, _Copy._data, _size * sizeof(_Ty));
        }

        // Copy an existing array.
        limited_array(limited_array&& _Right) noexcept
            : _size(_Right.size())
            , _data(_alloc.allocate(_size))
            , _ptr(_data) {
            STD::memcpy(_data, _Right._data, _size * sizeof(_Ty));
            _Right.~limited_array();
        }

        // Construct an instance by given size.
        limited_array(const size_t& _Size)
            : _size(_Size)
            , _data(_alloc.allocate(_size))
            , _ptr(_data) {
            for (_Ty* p = _data; p < _data + _size; p++) {
                new(p) _Ty();
            }
        }

        // Copy an existing array.
        limited_array(const _Ty* _Arr, const size_t& _Size)
            : _size(_Size)
            , _data(_alloc.allocate(_size))
            , _ptr(_data) {
            STD::memcpy(_data, _Arr, _size * sizeof(_Ty));
        }

        // Initialize by given items.
        limited_array(const STD::initializer_list<_Ty>& _Items)
            : _size(_Items.size())
            , _data(_alloc.allocate(_size))
            , _ptr(_data) {
            STD::memcpy(_data, _Items.begin(), _size * sizeof(_Ty));
        }

        // Copy an existing array.
        limited_array& operator=(const limited_array& _Copy) {
            if (&_Copy != this) {
                tidy();
                _alloc.deallocate(_data, _size);
                _data = _alloc.allocate(_size);
                _size = _Copy._size;
                STD::memcpy(_data, _Copy._data, _size * sizeof(_Ty));
            }
            return *this;
        }

        // Copy an existing array.
        limited_array& operator=(limited_array&& _Right) {
            if (&_Right != this) {
                tidy();
                _alloc.deallocate(_data, _size);
                _data = _alloc.allocate(_size);
                _size = _Right._size;
                STD::memcpy(_data, _Right._data, _size * sizeof(_Ty));
                _Right.~limited_array();
            }
            return *this;
        }

        // Move the pointer to the next data.
        _Ty& get_move() const {
            if (!check(_ptr)) {
                out_range();
            }
            return *_ptr++;
        }

        // Reset the pointer to the head.
        inline void reset() const {
            _ptr = _data;
        }

        // Convert to an array.
        inline explicit operator _Ty* () const {
            return _data;
        }

        // The size of the array.
        inline const size_t size() const {
            return _size;
        }

        // Indicates whether internal pointer is in range.
        inline bool in_range() const {
            return check(_ptr);
        }

        // Destroy the array.
        ~limited_array() {
            tidy();
            _alloc.deallocate(_data, _size);
        }
    };

    template <typename _Ty>
    STD::allocator<_Ty> limited_array<_Ty>::_alloc;

    // A random-access array whose size is given and of memory-safe.
    template <typename _Ty>
    class array
        : public limited_array<_Ty> {
    public:
        // The base class of the array.
        using _Base = limited_array<_Ty>;

        // Construct an instance by given size.
        array(const size_t& _Size)
            : _Base(_Size) {
        }

        // Copy an existing array.
        array(const _Ty* _Arr, const size_t& _Size)
            : _Base(_Arr, _Size) {
        }

        // Initialize by given items.
        array(const STD::initializer_list<_Ty>& _Items)
            : _Base(_Items) {
        }

        // Copy an existing array.
        array(const array& _Copy)
            : _Base(_Copy) {
        }

        // Copy an existing array.
        array(array&& _Right) noexcept
            : _Base(_Right) {
        }

        // Copy an existing array.
        array& operator=(const array& _Copy) {
            static_cast<_Base&>(*this) = static_cast<_Base&>(_Copy);
            return *this;
        }

        // Copy an existing array.
        array& operator=(array&& _Right) {
            static_cast<_Base&>(*this) = static_cast<_Base&&>(_Right);
            return *this;
        }

        // Support random access.
        _Ty& operator[](const size_t& _Id) const {
            _Ty* data_ptr = this->_data + _Id;
            this->check(data_ptr);
            return *data_ptr;
        }

        // Convert to a normal array.
        inline operator _Ty* () const {
            return this->data;
        }
    };

    // A helper class for tabulation.
    class table_printer {
    private:
        // Here comes the slope of tabulation code.
        static const char* TAB_TOP_LEFT,      *TAB_TOP_MIDDLE,    *TAB_TOP_MIDDLE_B,    *TAB_TOP_RIGHT;
        static const char* TAB_MIDDLE_LEFT,   *TAB_MIDDLE_MIDDLE, *TAB_MIDDLE_MIDDLE_B, *TAB_MIDDLE_RIGHT;
        static const char* TAB_BOTTOM_LEFT,   *TAB_BOTTOM_MIDDLE, *TAB_BOTTOM_MIDDLE_B, *TAB_BOTTOM_RIGHT;
        static const char* TAB_HOR_BORDER,    *TAB_HOR_BORDER_B,  *TAB_VER_BORDER,      *TAB_VER_BORDER_B;
        static const char* TAB_MIDDLE_LEFT_B, *TAB_LEFT_CORNER,   *TAB_MIDDLE_CORNER,   *TAB_RIGHT_CORNER;
        static const char* BASIC_CORNER,      *BASIC_HOR_BORDER,  *BASIC_VER_BORDER;

    public:
        static const char** top_left,    **top_spliter,    **top_middle,    **top_right;
        static const char** middle_left, **middle_spliter, **middle_middle, **middle_right;
        static const char** bottom_left, **bottom_spliter, **bottom_middle, **bottom_right;
        static const char** ver_border,  **ver_border_B,   **hor_border,    **hor_border_B;
        static const char** left_corner, **middle_corner,  **right_corner,  **middle_left_B;

        // Turn the table style to the basic one.
        static void basic_style() {
            top_left    = top_spliter    = top_middle    = top_right    = left_corner   = middle_left_B =
            middle_left = middle_spliter = middle_middle = middle_right = middle_corner = 
            bottom_left = bottom_spliter = bottom_middle = bottom_right = right_corner  = &BASIC_CORNER;
            ver_border  = ver_border_B   = &BASIC_VER_BORDER;
            hor_border  = hor_border_B   = &BASIC_HOR_BORDER;
        }

        // Turn the table style to the normal one.
        static void normal_style() {
            top_left      = &TAB_TOP_LEFT,      top_spliter    = &TAB_TOP_MIDDLE_B;
            top_middle    = &TAB_TOP_MIDDLE,    top_right      = &TAB_TOP_RIGHT;
            middle_left   = &TAB_MIDDLE_LEFT,   middle_spliter = &TAB_MIDDLE_MIDDLE_B;
            middle_middle = &TAB_MIDDLE_MIDDLE, middle_right   = &TAB_MIDDLE_RIGHT;
            bottom_left   = &TAB_BOTTOM_LEFT,   bottom_spliter = &TAB_BOTTOM_MIDDLE_B;
            bottom_middle = &TAB_BOTTOM_MIDDLE, bottom_right   = &TAB_BOTTOM_RIGHT;
            ver_border    = &TAB_VER_BORDER,    ver_border_B   = &TAB_VER_BORDER_B;
            hor_border    = &TAB_HOR_BORDER,    hor_border_B   = &TAB_HOR_BORDER_B;
            left_corner   = &TAB_LEFT_CORNER,   middle_corner  = &TAB_MIDDLE_CORNER;
            right_corner  = &TAB_RIGHT_CORNER,  middle_left_B  = &TAB_MIDDLE_LEFT_B;
        }

        // Print the border of chart whose cells' widths are same.
        static void print_border(size_t _Count, const size_t& _Cell_Width, const size_t& _Title_Width,
            const char* _Hor_Border, const char* _Left, const char* _Spliter, const char* _Middle, const char* _Right) {
            STD::cout << _Left << STT::duplicate(_Hor_Border, _Title_Width) << _Spliter;
            while (_Count--) {
                STD::cout << STT::duplicate(_Hor_Border, _Cell_Width) << (_Count ? _Middle : _Right);
            }
            STD::cout << PRT::NEW_LINE;
        }

        // Print the border the chart whose cells' widths vary.
        static void print_border(const size_t& _Title_Width, size_t* const _Widths, size_t _Widths_Length,
            const char* _Hor_Border, const char* _Left, const char* _Spliter, const char* _Middle, const char* _Right) {
            STD::cout << _Left;
            if (_Title_Width > 0) {
                STD::cout << STT::duplicate(_Hor_Border, _Title_Width) << _Spliter;
            }
            size_t* ptr = _Widths;
            while (_Widths_Length--) {
                STD::cout << STT::duplicate(_Hor_Border, *ptr++) << (_Widths_Length ? _Middle : _Right);
            }
            STD::cout << PRT::NEW_LINE;
        }

        // Print the border the chart whose cells' widths vary.
        inline static void print_border(const size_t& _Title_Width, const STD::initializer_list<size_t>& _Widths,
            const char* _Hor_Border, const char* _Left, const char* _Spliter, const char* _Middle, const char* _Right) {
            print_border(_Title_Width, const_cast<size_t*>(_Widths.begin()), _Widths.size(), _Hor_Border, _Left, _Spliter, _Middle, _Right);
        }

        // Print the border the chart whose cells' widths vary.
        static void print_border(const size_t& _Title_Width, const limited_array<print_format>& _Formats,
            const char* _Hor_Border, const char* _Left, const char* _Spliter, const char* _Middle, const char* _Right) {
            _Formats.reset();
            limited_array<size_t> widths(_Formats.size());
            for (size_t ptr = 0; ptr < _Formats.size(); ptr++) {
                widths.get_move() = _Formats.get_move().width;
            }
            print_border(_Title_Width, static_cast<size_t*>(widths), _Formats.size(), _Hor_Border, _Left, _Spliter, _Middle, _Right);
        }

        // Print the top border of chart whose cells' widths are same, and with normal spliter.
        inline static void border_top(const size_t& _Count, const size_t& _Width, const size_t& _Title_Width) {
            print_border(_Count, _Width, _Title_Width, *hor_border, *top_left, *top_middle, *top_middle, *top_right);
        }

        // Print the top border of chart whose cells' widths vary, and with normal spliter.
        inline static void border_top(const size_t& _Title_Width, const STD::initializer_list<size_t>& _Widths) {
            print_border(_Title_Width, _Widths, *hor_border, *top_left, *top_middle, *top_middle, *top_right);
        }

        // Print the top border of chart whose cells' widths vary, and with normal spliter.
        inline static void border_top(const size_t& _Title_Width, const limited_array<print_format>& _Widths) {
            print_border(_Title_Width, _Widths, *hor_border, *top_left, *top_middle, *top_middle, *top_right);
        }

        // Print the top border of chart whose cells' widths are same, and with bold spliter.
        inline static void border_top_spliter_B(const size_t& _Count, const size_t& _Width, const size_t& _Title_Width) {
            print_border(_Count, _Width, _Title_Width, *hor_border, *top_left, *top_spliter, *top_middle, *top_right);
        }

        // Print the top border of chart whose cells' widths vary, and with bold spliter.
        inline static void border_top_spliter_B(const size_t& _Title_Width, const STD::initializer_list<size_t>& _Widths) {
            print_border(_Title_Width, _Widths, *hor_border, *top_left, *top_spliter, *top_middle, *top_right);
        }

        // Print the top border of chart whose cells' widths vary, and with normal spliter.
        inline static void border_top_spliter_B(const size_t& _Title_Width, const limited_array<print_format>& _Widths) {
            print_border(_Title_Width, _Widths, *hor_border, *top_left, *top_spliter, *top_middle, *top_right);
        }

        // Print the middle border of chart whose cells' widths are same.
        inline static void border_middle(const size_t& _Count, const size_t& _Width, const size_t& _Title_Width) {
            print_border(_Count, _Width, _Title_Width, *hor_border, *middle_left, *middle_spliter, *middle_middle, *middle_right);
        }

        // Print the middle border of chart whose cells' widths are same.
        inline static void border_middle(const size_t& _Title_Width, const STD::initializer_list<size_t>& _Widths) {
            print_border(_Title_Width, _Widths, *hor_border, *middle_left, *middle_spliter, *middle_middle, *middle_right);
        }

        // Print the top border of chart whose cells' widths vary, and with normal spliter.
        inline static void border_middle(const size_t& _Title_Width, const limited_array<print_format>& _Widths) {
            print_border(_Title_Width, _Widths, *hor_border, *middle_left, *middle_spliter, *middle_middle, *middle_right);
        }

        // Print the middle border of chart whose cells' widths are same.
        inline static void border_middle_B(const size_t& _Count, const size_t& _Width, const size_t& _Title_Width) {
            print_border(_Count, _Width, _Title_Width, *hor_border_B, *middle_left_B, *middle_spliter, *middle_corner, *right_corner);
        }

        // Print the middle border of chart whose cells' widths are same.
        inline static void border_middle_B(const size_t& _Title_Width, const STD::initializer_list<size_t>& _Widths) {
            print_border(_Title_Width, _Widths, *hor_border_B, *middle_left_B, *middle_spliter, *middle_corner, *right_corner);
        }

        // Print the top border of chart whose cells' widths vary, and with normal spliter.
        inline static void border_middle_B(const size_t& _Title_Width, const limited_array<print_format>& _Widths) {
            print_border(_Title_Width, _Widths, *hor_border_B, *middle_left_B, *middle_spliter, *middle_corner, *right_corner);
        }

        // Print the bottom border of chart whose cells' widths are same.
        inline static void border_bottom(const size_t& _Count, const size_t& _Width, const size_t& _Title_Width) {
            print_border(_Count, _Width, _Title_Width, *hor_border, *bottom_left, *bottom_spliter, *bottom_middle, *bottom_right);
        }

        // Print the bottom border of chart whose cells' widths are same.
        inline static void border_bottom(const size_t& _Title_Width, const STD::initializer_list<size_t>& _Widths) {
            print_border(_Title_Width, _Widths, *hor_border, *bottom_left, *bottom_spliter, *bottom_middle, *bottom_right);
        }

        // Print the top border of chart whose cells' widths vary, and with normal spliter.
        inline static void border_bottom(const size_t& _Title_Width, const limited_array<print_format>& _Widths) {
            print_border(_Title_Width, _Widths, *hor_border, *bottom_left, *bottom_spliter, *bottom_middle, *bottom_right);
        }
    };

#define TAP table_printer

#define _SET_TABULATION_CHAR(_VARIABLE_, _VALUE_) \
    const char* TAP::_VARIABLE_ = _VALUE_;

    _SET_TABULATION_CHAR(TAB_TOP_LEFT,        "┌")
    _SET_TABULATION_CHAR(TAB_TOP_MIDDLE,      "┬")
    _SET_TABULATION_CHAR(TAB_TOP_MIDDLE_B,    "┰")
    _SET_TABULATION_CHAR(TAB_TOP_RIGHT,       "┐")
    _SET_TABULATION_CHAR(TAB_MIDDLE_LEFT,     "├")
    _SET_TABULATION_CHAR(TAB_MIDDLE_MIDDLE,   "┼")
    _SET_TABULATION_CHAR(TAB_MIDDLE_MIDDLE_B, "╂")
    _SET_TABULATION_CHAR(TAB_MIDDLE_RIGHT,    "┤")
    _SET_TABULATION_CHAR(TAB_BOTTOM_LEFT,     "└")
    _SET_TABULATION_CHAR(TAB_BOTTOM_MIDDLE,   "┴")
    _SET_TABULATION_CHAR(TAB_BOTTOM_MIDDLE_B, "┸")
    _SET_TABULATION_CHAR(TAB_BOTTOM_RIGHT,    "┘")
    _SET_TABULATION_CHAR(TAB_HOR_BORDER,      "─")
    _SET_TABULATION_CHAR(TAB_HOR_BORDER_B,    "━")
    _SET_TABULATION_CHAR(TAB_VER_BORDER,      "│")
    _SET_TABULATION_CHAR(TAB_VER_BORDER_B,    "┃")
    _SET_TABULATION_CHAR(TAB_MIDDLE_LEFT_B,   "┝")
    _SET_TABULATION_CHAR(TAB_LEFT_CORNER,     "╆")
    _SET_TABULATION_CHAR(TAB_MIDDLE_CORNER,   "┿")
    _SET_TABULATION_CHAR(TAB_RIGHT_CORNER,    "┥")
    _SET_TABULATION_CHAR(BASIC_CORNER,        "+")
    _SET_TABULATION_CHAR(BASIC_HOR_BORDER,    "-")
    _SET_TABULATION_CHAR(BASIC_VER_BORDER,    "|")

#undef _SET_TABULATION_CHAR

#define _SET_TABULATION_CHAR_POINTER(_VARIABLE_, _TARGET_) \
    const char** TAP::_VARIABLE_ = &TAP::_TARGET_;

    _SET_TABULATION_CHAR_POINTER(top_left,       TAB_TOP_LEFT       )
    _SET_TABULATION_CHAR_POINTER(top_middle,     TAB_TOP_MIDDLE     )
    _SET_TABULATION_CHAR_POINTER(middle_left,    TAB_MIDDLE_LEFT    )
    _SET_TABULATION_CHAR_POINTER(middle_middle,  TAB_MIDDLE_MIDDLE  )
    _SET_TABULATION_CHAR_POINTER(bottom_left,    TAB_BOTTOM_LEFT    )
    _SET_TABULATION_CHAR_POINTER(bottom_middle,  TAB_BOTTOM_MIDDLE  )
    _SET_TABULATION_CHAR_POINTER(ver_border,     TAB_VER_BORDER     )
    _SET_TABULATION_CHAR_POINTER(hor_border,     TAB_HOR_BORDER     )
    _SET_TABULATION_CHAR_POINTER(left_corner,    TAB_LEFT_CORNER    )
    _SET_TABULATION_CHAR_POINTER(right_corner,   TAB_RIGHT_CORNER   )
    _SET_TABULATION_CHAR_POINTER(top_spliter,    TAB_TOP_MIDDLE_B   )
    _SET_TABULATION_CHAR_POINTER(top_right,      TAB_TOP_RIGHT      )
    _SET_TABULATION_CHAR_POINTER(middle_spliter, TAB_MIDDLE_MIDDLE_B)
    _SET_TABULATION_CHAR_POINTER(middle_right,   TAB_MIDDLE_RIGHT   )
    _SET_TABULATION_CHAR_POINTER(bottom_spliter, TAB_BOTTOM_MIDDLE_B)
    _SET_TABULATION_CHAR_POINTER(bottom_right,   TAB_BOTTOM_RIGHT   )
    _SET_TABULATION_CHAR_POINTER(ver_border_B,   TAB_VER_BORDER_B   )
    _SET_TABULATION_CHAR_POINTER(hor_border_B,   TAB_HOR_BORDER_B   )
    _SET_TABULATION_CHAR_POINTER(middle_corner,  TAB_MIDDLE_CORNER  )
    _SET_TABULATION_CHAR_POINTER(middle_left_B,  TAB_MIDDLE_LEFT_B  )

#undef _SET_TABULATION_CHAR_POINTER

    // Print an id or a range of id into a cell.
    void PRT::print_id(const size_t& _Start, const size_t& _End, const size_t& _Width) {
        if (_Start < _End) {
            STD::cout << *TAP::ver_border << STT::center(_Start, 3, false) << '-' << STT::center(_End, 3, true) << *TAP::ver_border_B;
        }
        else {
            STD::cout << *TAP::ver_border << STT::center(_Start, _Width, false) << *TAP::ver_border_B;
        }
    }

    // An object which can be null.
    template <typename _Ty>
    class nullable_object {
    private:
        static STD::allocator<_Ty> _alloc;              // The allocator to allocate a space of memory for _Ty.
        _Ty*                       _data   = nullptr;   // The pointer to the data.
        bool                       _is_null;            // Indicates whether the object is null.

    public:
        // Construct a null instance.
        nullable_object()
            : _is_null(true) {
        }

        // Copy an existing instance.
        nullable_object(const nullable_object& _Copy)
            : _is_null(_Copy._is_null) {
            if (!_is_null) {
                _data = _alloc.allocate(1);
                new(_data) _Ty(*_Copy._data);
            }
        }

        // Copy an existing instance.
        nullable_object(nullable_object&& _Right) noexcept
            : _is_null(_Right._is_null) {
            if (!_is_null) {
                _data = _alloc.allocate(1);
                new(_data) _Ty(*_Right._data);
                _Right.clear();
            }
        }

        // Construct an instance with given value.
        nullable_object(const _Ty& _Value)
            : _is_null(false)
            , _data(_alloc.allocate(1)) {
            new(_data) _Ty(_Value);
        }

        // Construct an instance with given value.
        nullable_object(_Ty&& _Right)
            : _is_null(false)
            , _data(_alloc.allocate(1)) {
            new(_data) _Ty(_Right);
        }

        // Destroy the object.
        ~nullable_object() {
            if (!_is_null) {
                clear();
            }
        }

        // Copy an existing instance.
        nullable_object& operator=(const nullable_object& _Copy) {
            if (this != &_Copy) {
                clear();
                _is_null  = _Copy._is_null;
                if (!_is_null) {
                    _data = _alloc.allocate(1);
                    new(_data) _Ty(*_Copy._data);
                }
            }
            return *this;
        }

        // Copy an existing instance.
        nullable_object& operator=(nullable_object&& _Right) noexcept {
            if (this != &_Right) {
                clear();
                _is_null  = _Right._is_null;
                if (!_is_null) {
                    _data = _alloc.allocate(1);
                    new(_data) _Ty(*_Right._data);
                    _Right.clear();
                }
            }
            return *this;
        }

        // Set the data a new value.
        void operator=(const _Ty& _Val) {
            if (_is_null) {
                _data    = _alloc.allocate(1);
                _is_null = false;
            }
            new(_data) _Ty(_Val);
        }

        // Indicates whether the given two object's data is value-same.
        bool operator==(const nullable_object& _Val) {
            return *_data == *_Val._data;
        }

        // Get the data object.
        inline const _Ty& object() const {
            return *_data;
        }

        // Indicates whether the object is null.
        inline bool is_null() const {
            return _is_null;
        }

        // Run functions of the data.
        inline _Ty* operator->() const {
            return _data;
        }

        // Destroy the object and deallocate its memory.
        void clear() {
            if (_is_null) {
                return;
            }
            _data->~_Ty();
            _alloc.deallocate(_data, 1);
            _data    = nullptr;
            _is_null = true;
        }
    };

    template <typename _Ty>
    STD::allocator<_Ty> nullable_object<_Ty>::_alloc;

    // Describe a row of table.
    template <typename... _Ty>
    class row;

    // The helper class for getting elements of a row.
    template <size_t _Id, typename _Row>
    struct row_element;

    // Describe a table whose each column's type is given.
    template <typename _Colty1, typename... _Coltys>
    class table;

    // The helper class for getting elements of a row.
    template <size_t _Id, typename _Row>
    struct row_element {
        using _Type = typename row_element<_Id - 1, typename _Row::_Base>::_Type;
    };

    // The helper class for getting elements of a row.
    template <typename _Row>
    struct row_element<0, _Row> {
        using _Type = _Row;
    };

    // Describe a row of table.
    template <>
    class row<> {
    public:
        // The base class of the row.
        using _Base = void;

        // Print the elements of the row.
        void print(const limited_array<print_format>& _Formats) {
            STD::cout << PRT::NEW_LINE;
            _Formats.reset();
        }
    };

    // Describe a row of table.
    template <typename _Thisty, typename... _Coltys>
    class row<_Thisty, _Coltys...>
        : public row<_Coltys...> {

        template <size_t _Id, typename _Row>
        friend struct row_element;

        template <typename __Thisty, typename... __Coltys>
        friend class table;

    public:
        using _Base = row<_Coltys...>;  // The base class of the row.
        nullable_object<_Thisty> value; // The current element in this level of the row.

        // Construct a new row.
        row()
            : _Base() {
        }

        // Print the elements of the row.
        void print(const limited_array<print_format>& _Formats) {
            if (!value.is_null()) {
                _Formats.get_move().print_incell(value.object());
                STD::cout << *TAP::ver_border;
            }
            else {
                STD::cout << STT::duplicate(' ', _Formats.get_move().width) << *TAP::ver_border;
            }
            get_base().print(_Formats);
        }

        // Gets the element of the specified column in the row.
        template <size_t _Id>
        constexpr auto& column() {
            using _Type = typename row_element<_Id, row<_Thisty, _Coltys...>>::_Type;
            return static_cast<_Type&>(*this).value;
        }

    private:
        // Get the base class.
        inline _Base& get_base() {
            return *this;
        }
    };

    // Describe a table whose each column's type is given.
    template <typename _Colty1, typename... _Coltys>
    class table {
    public:
        using _Rowty = row<_Colty1, _Coltys...>;        // Row type of the table.
        nullable_object<STD::string>        title;      // Title of the table.
        array<nullable_object<STD::string>> headers;    // Headers of the table.

    private:
        STD::vector<_Rowty>         _rows;              // Rows of the table.
        limited_array<print_format> _formats;           // Formats of each column.

    public:
        // Construct a new table whose columns' data type are all built-in.
        table()
            : headers(1 + sizeof...(_Coltys))
            , _formats(1 + sizeof...(_Coltys)) {
            limited_array<print_format> _formats(0);
            get_formats<_Colty1, _Coltys...>(_formats);
            _formats.reset();
        }

        // Construct a new table which has a column's data type which is not built-in. 
        table(const print_format& _Format)
            : headers(1 + sizeof...(_Coltys))
            , _formats(1 + sizeof...(_Coltys)) {
            limited_array<print_format> _formats(&_Format, 1);
            get_formats<_Colty1, _Coltys...>(_formats);
            _formats.reset();
        }

        // Construct a new table which has some columns' data type which are not built-in. 
        table(const STD::initializer_list<print_format>& _Formats)
            : headers(1 + sizeof...(_Coltys))
            , _formats(1 + sizeof...(_Coltys)) {
            limited_array<print_format> _formats(_Formats.begin(), _Formats.size());
            get_formats<_Colty1, _Coltys...>(_formats);
            _formats.reset();
        }

        // Get the row by given id.
        inline _Rowty& operator[](const size_t& _Row_Id) {
            return _rows[_Row_Id];
        }

        // Add a new row.
        inline _Rowty& add_row() {
            _rows.emplace_back();
            return _rows[_rows.size() - 1];
        }

        // Romove an indicated row.
        inline void remove_row(const size_t& _Id) {
            _rows.erase(_rows.begin() + _Id);
        }

        // Clear all the rows.
        inline void clear() const {
            _rows.clear();
        }

        // Print the table.
        void print() {
            if (_rows.size() == 0) {
                return;
            }
            headers.reset();
            bool has_header = false;
            limited_array<print_format> _fit_formats = fit_header(has_header);
            if (!title.is_null()) {
                size_t width = get_table_width(_fit_formats);
                STD::cout << STT::center(title.object(), width, true) << PRT::NEW_LINE;
            }
            if (has_header) {
                TAP::border_top(0, _fit_formats);
                STD::cout << *TAP::ver_border;
                headers.reset();
                _fit_formats.reset();
                while (headers.in_range() && _fit_formats.in_range()) {
                    nullable_object<STD::string>& h_ptr = headers.get_move();
                    print_format& f_ptr = _fit_formats.get_move();
                    if (!h_ptr.is_null()) {
                        STD::cout << STT::center(h_ptr.object(), f_ptr.width, true);
                    }
                    else {
                        STD::cout << STT::duplicate(' ', f_ptr.width);
                    }
                    STD::cout << *TAP::ver_border;
                }
                STD::cout << PRT::NEW_LINE;
                TAP::border_middle_B(0, _fit_formats);
            }
            else {
                TAP::border_top(0, _fit_formats);
            }
            for (size_t r_ptr = 0; r_ptr < _rows.size(); r_ptr++) {
                STD::cout << *TAP::ver_border;
                _fit_formats.reset();
                _rows[r_ptr].print(_fit_formats);
                if (r_ptr < _rows.size() - 1) {
                    TAP::border_middle(0, _fit_formats);
                }
                else {
                    TAP::border_bottom(0, _fit_formats);
                }
            }
        }

    private:
        // Matches formats of each columns.
        template <typename __Colty1>
        is_built_in_t<__Colty1> get_formats(const limited_array<print_format>& _Formats) {
            _formats.get_move() = get_built_in_format<__Colty1>();
        }

        // Matches formats of each columns.
        template <typename __Colty1>
        STD::enable_if_t<is_not_built_in_v<__Colty1>> get_formats(const limited_array<print_format>& _Formats) {
            _formats.get_move() = _Formats.get_move();
        }

        // Matches formats of each columns.
        template <typename __Colty1, typename... __Coltys>
        STD::enable_if_t<(sizeof...(__Coltys)) && is_built_in_v<__Colty1>> get_formats(const limited_array<print_format>& _Formats) {
            _formats.get_move() = get_built_in_format<__Colty1>();
            get_formats<__Coltys...>(_Formats);
        }

        // Matches formats of each columns.
        template <typename __Colty1, typename... __Coltys>
        STD::enable_if_t<(sizeof...(__Coltys)) && is_not_built_in_v<__Colty1>> get_formats(const limited_array<print_format>& _Formats) {
            _formats.get_move() = _Formats.get_move();
            get_formats<__Coltys...>(_Formats);
        }

        // Get the width of the table.
        size_t get_table_width(const limited_array<print_format>& _Formats) {
            size_t width = 1;
            _Formats.reset();
            while (_Formats.in_range()) {
                width += _Formats.get_move().width + 1;
            }
            return width;
        }

        // Automatically fit the headers.
        limited_array<print_format> fit_header(bool& _Has_Header) {
            limited_array<print_format> fit_formats(_formats);
            headers.reset();
            while (fit_formats.in_range() && headers.in_range()) {
                print_format& f_ptr = fit_formats.get_move();
                nullable_object<STD::string>& s_ptr = headers.get_move();
                if (!s_ptr.is_null()) {
                    _Has_Header = true;
                    if (s_ptr->size() > f_ptr.width) {
                        f_ptr.width = s_ptr->size();
                    }
                }
            }
            return fit_formats;
        }
    };

    // A helper class for peeping access-limited containers.
    class peep_tool {
    public:
        // Get items of the container.
        template <typename _Container>
        inline static STD::vector<typename _Container::value_type> get_items(const _Container& _Con) {
            return STD::vector<typename _Container::value_type>(_Con.begin(), _Con.end());
        }

        // A helper class to get items of std::stack.
        template <typename _Ty, typename _Container = STD::deque<_Ty>>
        class peeped_stack
            : public STD::stack<_Ty, _Container> {
        public:
            // The base class of peeped_stack.
            using _Base = STD::stack<_Ty, _Container>;

            // Construct an instance by given std::stack.
            peeped_stack(const _Base& _Stack)
                : _Base(_Stack) {
            }

            // Construct an instance by given std::stack.
            peeped_stack(_Base&& _Stack)
                : _Base(_Stack) {
            }

            // Get the items of the inside container.
            inline STD::vector<_Ty> get_items() const {
                return peep_tool::get_items(this->c);
            }
        };

        // A helper class to get items of queue.
        template <typename _Ty, typename _Container = STD::deque<_Ty>>
        class peeped_queue
            : public STD::queue<_Ty, _Container> {
        public:
            // The base class of peeped_queue.
            using _Base = STD::queue<_Ty, _Container>;

            // Construct an instance by given std::queue.
            peeped_queue(const _Base& _Queue)
                : _Base(_Queue) {
            }

            // Construct an instance by given std::queue.
            peeped_queue(_Base&& _Queue)
                : _Base(_Queue) {
            }

            // Get the items of the inside container.
            inline STD::vector<_Ty> get_items() const {
                return peep_tool::get_items(this->c);
            }
        };

        // A helper class to get items of std::priority_queue.
        template <typename _Ty, typename _Container = STD::vector<_Ty>, typename _Pr = STD::less<typename _Container::value_type>>
        class peeped_priority_queue
            : public STD::priority_queue<_Ty, _Container, _Pr> {
        public:
            // The base class of peeped_priority_queue.
            using _Base = STD::priority_queue<_Ty, _Container, _Pr>;

            // Construct an instance by given std::priority_queue.
            peeped_priority_queue(const _Base& _Queue)
                : _Base(_Queue) {
            }

            // Construct an instance by given std::priority_queue.
            peeped_priority_queue(_Base&& _Queue)
                : _Base(_Queue) {
            }

            // Get the items of the inside container.
            inline STD::vector<_Ty> get_items() const {
                return peep_tool::get_items(this->c);
            }
        };

        // Peep inside items of std::stack.
        template <typename _Ty, typename _Container>
        inline static STD::vector<_Ty> peep(const STD::stack<_Ty, _Container>& _Stack) {
            return static_cast<peeped_stack<_Ty, _Container>>(_Stack).get_items();
        }

        // Peep inside items of std::queue.
        template <typename _Ty, typename _Container>
        inline static STD::vector<_Ty> peep(const STD::queue<_Ty, _Container>& _Queue) {
            return static_cast<peeped_queue<_Ty, _Container>>(_Queue).get_items();
        }

        // Peep inside items of std::priority_queue.
        template <typename _Ty, typename _Container, typename _Pr>
        inline static STD::vector<_Ty> peep(const STD::priority_queue<_Ty, _Container, _Pr>& _Queue) {
            return static_cast<peeped_priority_queue<_Ty, _Container, _Pr>>(_Queue).get_items();
        }
    };

    // Here comes the slope for printing single value.

    // Print value of _Ty with given format.
    template <typename _Ty>
    is_printable_t<_Ty> print(const _Ty& _Val, const print_format& _Format, const char* _Name) {
        STD::cout << '@' << (void*)(&_Val) << ' ' << _Format.name << ' ' << _Name << " = ";
        _Format.print_inline(_Val);
        STD::cout << PRT::NEW_LINE;
    }

    // Print value of built-in _Ty.
    template <typename _Ty>
    is_built_in_t<_Ty> print(const _Ty& _Val, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        STD::cout << '@' << (void*)(&_Val) << ' ' << format.name << ' ' << _Name << " = ";
        format.print_inline(_Val);
        STD::cout << PRT::NEW_LINE;
    }

    // Print C-style string.
    inline void print(char* const _Ptr, const char* _Name) {
        STD::cout << '@' << (void*)(_Ptr) << " char* " << _Name << " = \"" << _Ptr << "\"\n";
    }

    // Print std::string.
    inline void print(const STD::string& _Str, const char* _Name) {
        STD::cout << '@' << (void*)(&_Str) << " std::string " << _Name << " = \"" << _Str << "\"\n";
    }

    // Here comes the slope for printing one-dimensional-array-like value.
    
    // The base function for printing a chart whose cells are filled with values.
    template <typename _Ty>
    is_printable_t<_Ty> print(const STD::function<_Ty(size_t)>& _Val_Func, const print_format& _Format, const size_t& _Len) {
        size_t rows = PRT::ceil_divide(_Len, _Format.length);
        if (rows == 0) {
            return;
        }
        size_t length = STD::min(_Len, _Format.length);
        size_t title_width = (length == 1) ? 3 : 7;
        TAP::border_top_spliter_B(length, _Format.width, title_width);
        for (size_t row = 0; row < rows; row++) {
            PRT::print_id(row * _Format.length, STD::min(_Len - 1, (row + 1) * _Format.length - 1), title_width);
            for (size_t col = 0; col < _Format.length; col++) {
                if (row * _Format.length + col < _Len) {
                    _Format.print_incell(_Val_Func(row * _Format.length + col));
                    STD::cout << *TAP::ver_border;
                }
                else if (rows > 1) {
                    STD::cout << STT::duplicate(' ', _Format.width) << *TAP::ver_border;
                }
            }
            STD::cout << PRT::NEW_LINE;
            if (row < rows - 1) {
                TAP::border_middle(_Format.length, _Format.width, title_width);
            }
            else {
                TAP::border_bottom(length, _Format.width, title_width);
            }
        }
    }

    // C-style array //

    // Print one-dimensional-array of built-in _Ty.
    template <typename _Ty>
    is_built_in_t<_Ty> print(_Ty* const _Ptr, const size_t& _Len, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        STD::cout << '@' << (void*)(_Ptr) << ' ' << format.name << ' ' << _Name << '[' << _Len << "]:\n";
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return _Ptr[_ptr]; };
        print(func, format, _Len);
    }

    // Print one-dimensional-array of built-in _Ty.
    template <typename _Ty, size_t _Len>
    is_built_in_t<_Ty> print(const _Ty (&_Arr)[_Len], const char* _Name) {
        print((_Ty*)_Arr, _Len, _Name);
    }

    // Print one-dimensional-array of _Ty with given format.
    template <typename _Ty>
    is_printable_t<_Ty> print(_Ty* const _Ptr, const print_format& _Format, const size_t& _Len, const char* _Name) {
        STD::cout << '@' << (void*)(_Ptr) << ' ' << _Format.name << ' ' << _Name << '[' << _Len << "]:\n";
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return _Ptr[_ptr]; };
        print(func, _Format, _Len);
    }

    // Print one-dimensional-array of _Ty with given format.
    template <typename _Ty, size_t _Len>
    is_printable_t<_Ty> print(const _Ty (&_Arr)[_Len], const print_format& _Format, const char* _Name) {
        print((_Ty*)_Arr, _Format, _Len, _Name);
    }

    // Print one-dimensional-array of C-style string.
    void print(char** const _Ptr, const size_t& _Len_Arr, const size_t& _Len_Str, const char* _Name) {
        STD::cout << '@' << (void*)(_Ptr) << " char " << _Name << '[' << _Len_Arr << "][" << _Len_Str << "]:\n";
        STD::function<char*(size_t)> func = [&](const size_t& _row) -> char* { return (char*)_Ptr + _row * _Len_Str; };
        print(func, get_built_in_format<char*>(), _Len_Arr);
    }

    // Print one-dimensional-array of C-style string.
    template <size_t _Len_Arr, size_t _Len_Str>
    void print(const char (&_Arr)[_Len_Arr][_Len_Str], const char* _Name) {
        STD::cout << '@' << (void*)(_Arr) << " char " << _Name << '[' << _Len_Arr << "][" << _Len_Str << "]:\n";
        STD::function<char*(size_t)> func = [&](const size_t& _row) -> char* { return (char*)_Arr + _row * _Len_Str; };
        print(func, get_built_in_format<char*>(), _Len_Arr);
    }

    // std::vector //

    // Print std::vector<_Ty, _Alloc> where _Ty is built-in type.
    template <typename _Ty, typename _Alloc>
    is_built_in_t<_Ty> print(const STD::vector<_Ty, _Alloc>& _Vector, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        PRT::tip(_Vector, "std::vector", format.name, _Name, _Vector.size());
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return _Vector[_ptr]; };
        print(func, format, _Vector.size());
    }

    // Print std::vector<_Ty, _Alloc> with given format.
    template <typename _Ty, typename _Alloc>
    is_printable_t<_Ty> print(const STD::vector<_Ty, _Alloc>& _Vector, const print_format& _Format, const char* _Name) {
        PRT::tip(_Vector, "std::vector", _Format.name, _Name, _Vector.size());
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return _Vector[_ptr]; };
        print(func, _Format, _Vector.size());
    }

    // std::deque //

    // Print std::deque<_Ty, _Alloc> where _Ty is built-in type.
    template <typename _Ty, typename _Alloc>
    is_built_in_t<_Ty> print(const STD::deque<_Ty, _Alloc>& _Deque, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        PRT::tip(_Deque, "std::deque", format.name, _Name, _Deque.size());
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return _Deque[_ptr]; };
        print(func, format, _Deque.size());
    }

    // Print std::deque<_Ty, _Alloc> with given format.
    template <typename _Ty, typename _Alloc>
    is_printable_t<_Ty> print(const STD::deque<_Ty, _Alloc>& _Deque, const print_format& _Format, const char* _Name) {
        PRT::tip(_Deque, "std::deque", _Format.name, _Name, _Deque.size());
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return _Deque[_ptr]; };
        print(func, _Format, _Deque.size());
    }
    
    // std::set //

    // Print std::set<_Ty, _Pr, _Alloc> where _Ty is built-in type.
    template <typename _Ty, typename _Pr, typename _Alloc>
    is_built_in_t<_Ty> print(const STD::set<_Ty, _Pr, _Alloc>& _Set, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        PRT::tip(_Set, "std::set", format.name, _Name, _Set.size());
        auto iter = _Set.begin();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return *iter++; };
        print(func, format, _Set.size());
    }

    // Print std::set<_Ty, _Pr, _Alloc> with given format.
    template <typename _Ty, typename _Pr, typename _Alloc>
    is_printable_t<_Ty> print(const STD::set<_Ty, _Pr, _Alloc>& _Set, const print_format& _Format, const char* _Name) {
        PRT::tip(_Set, "std::set", _Format.name, _Name, _Set.size());
        auto iter = _Set.begin();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return *iter++; };
        print(func, _Format, _Set.size());
    }

    // std::unordered_set //

    // Print std::unordered_set<_Ty, _Hasher, _Keyeq, _Alloc> where _Ty is built-in type.
    template <typename _Ty, typename _Hasher, typename _Keyeq, typename _Alloc>
    is_built_in_t<_Ty> print(const STD::unordered_set<_Ty, _Hasher, _Keyeq, _Alloc>& _Set, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        PRT::tip(_Set, "std::unordered_set", format.name, _Name, _Set.size());
        auto iter = _Set.begin();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return *iter++; };
        print(func, format, _Set.size());
    }

    // Print std::unordered_set<_Ty, _Hasher, _Keyeq, _Alloc> with given format.
    template <typename _Ty, typename _Hasher, typename _Keyeq, typename _Alloc>
    is_printable_t<_Ty> print(const STD::unordered_set<_Ty, _Hasher, _Keyeq, _Alloc>& _Set, const print_format& _Format, const char* _Name) {
        PRT::tip(_Set, "std::unordered_set", _Format.name, _Name, _Set.size());
        auto iter = _Set.begin();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return *iter++; };
        print(func, _Format, _Set.size());
    }

    // std::multiset //

    // Print std::multiset<_Ty, _Pr, _Alloc> where _Ty is built-in type.
    template <typename _Ty, typename _Pr, typename _Alloc>
    is_built_in_t<_Ty> print(const STD::multiset<_Ty, _Pr, _Alloc>& _Set, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        PRT::tip(_Set, "std::multiset", format.name, _Name, _Set.size());
        auto iter = _Set.begin();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return *iter++; };
        print(func, format, _Set.size());
    }

    // Print std::multiset<_Ty, _Pr, _Alloc> with given format.
    template <typename _Ty, typename _Pr, typename _Alloc>
    is_printable_t<_Ty> print(const STD::multiset<_Ty, _Pr, _Alloc>& _Set, const print_format& _Format, const char* _Name) {
        PRT::tip(_Set, "std::multiset", _Format.name, _Name, _Set.size());
        auto iter = _Set.begin();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return *iter++; };
        print(func, _Format, _Set.size());
    }

    // std::unordered_multiset //

    // Print std::unordered_multiset<_Ty, _Hasher, _Keyeq, _Alloc> where _Ty is built-in type.
    template <typename _Ty, typename _Hasher, typename _Keyeq, typename _Alloc>
    is_built_in_t<_Ty> print(const STD::unordered_multiset<_Ty, _Hasher, _Keyeq, _Alloc>& _Set, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        PRT::tip(_Set, "std::unordered_multiset", format.name, _Name, _Set.size());
        auto iter = _Set.begin();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return *iter++; };
        print(func, format, _Set.size());
    }

    // Print std::unordered_multiset<_Ty, _Hasher, _Keyeq, _Alloc> with given format.
    template <typename _Ty, typename _Hasher, typename _Keyeq, typename _Alloc>
    is_printable_t<_Ty> print(const STD::unordered_multiset<_Ty, _Hasher, _Keyeq, _Alloc>& _Set, const print_format& _Format, const char* _Name) {
        PRT::tip(_Set, "std::unordered_multiset", _Format.name, _Name, _Set.size());
        auto iter = _Set.begin();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return *iter++; };
        print(func, _Format, _Set.size());
    }

    // std::list //

    // Print std::list<_Ty, _Alloc> where _Ty is built-in type.
    template <typename _Ty, typename _Alloc>
    is_built_in_t<_Ty> print(const STD::list<_Ty, _Alloc>& _List, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        PRT::tip(_List, "std::list", format.name, _Name, _List.size());
        auto iter = _List.begin();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return *iter++; };
        print(func, format, _List.size());
    }

    // Print std::list<_Ty, _Alloc> with given format.
    template <typename _Ty, typename _Alloc>
    is_printable_t<_Ty> print(const STD::list<_Ty, _Alloc>& _List, const print_format& _Format, const char* _Name) {
        PRT::tip(_List, "std::list", _Format.name, _Name, _List.size());
        auto iter = _List.begin();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return *iter++; };
        print(func, _Format, _List.size());
    }

    // std::array //

    // Print std::array<_Ty, _Size> where _Ty is built-in type.
    template <typename _Ty, size_t _Size>
    is_built_in_t<_Ty> print(const STD::array<_Ty, _Size>& _Arr, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        PRT::tip(_Arr, "std::array", format.name, _Name, _Arr.size());
        auto iter = _Arr.begin();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return *iter++; };
        print(func, format, _Size);
    }

    // Print std::array<_Ty, _Size> with given format.
    template <typename _Ty, size_t _Size>
    is_printable_t<_Ty> print(const STD::array<_Ty, _Size>& _Arr, const print_format& _Format, const char* _Name) {
        PRT::tip(_Arr, "std::array", _Format.name, _Name, _Arr.size());
        auto iter = _Arr.begin();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return *iter++; };
        print(func, _Format, _Size);
    }

    // preinte::limited_array & preinte::array //

    // Print preinte::limited_array<_Ty> where _Ty is built-in type.
    template <typename _Ty>
    is_built_in_t<_Ty> print(const limited_array<_Ty>& _Arr, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        PRT::tip(_Arr, "preinte::limited_array", format.name, _Name, _Arr.size());
        _Arr.reset();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return _Arr.get_move(); };
        print(func, format, _Arr.size());
    }

    // Print preinte::limited_array<_Ty> with given format.
    template <typename _Ty>
    is_printable_t<_Ty> print(const limited_array<_Ty>& _Arr, const print_format& _Format, const char* _Name) {
        PRT::tip(_Arr, "preinte::limited_array", _Format.name, _Name, _Arr.size());
        _Arr.reset();
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return _Arr.get_move(); };
        print(func, _Format, _Arr.size());
    }

    template <typename _Ty>
    is_built_in_t<_Ty> print(const array<_Ty>& _Arr, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        PRT::tip(_Arr, "preinte::array", format.name, _Name, _Arr.size());
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return _Arr[_ptr]; };
        print(func, format, _Arr.size());
    }

    template <typename _Ty>
    is_built_in_t<_Ty> print(const array<_Ty>& _Arr, const print_format& _Format, const char* _Name) {
        PRT::tip(_Arr, "preinte::array", _Format.name, _Name, _Arr.size());
        STD::function<_Ty(size_t)> func = [&](const size_t& _ptr) -> _Ty { return _Arr[_ptr]; };
        print(func, _Format, _Arr.size());
    }

    // linked-list //

    // Print linked list whose node format and head are given.
    template <typename _NodeTy, typename _DataTy>
    is_printable_t<_DataTy> print(_NodeTy* const _Head, const linked_node_format<_NodeTy, _DataTy>& _Node_Format, const char* _Name) {
        STD::cout << '@' << (void*)(_Head) << ' ' << _Node_Format.node_name << ' ' << _Name << "[length = ";
        STD::vector<_DataTy*> repository;
        _NodeTy* ptr = _Head;
        while (ptr != nullptr) {
            repository.push_back(&(_Node_Format.get_data(ptr)));
            ptr = _Node_Format.get_next(ptr);
        }
        STD::cout << repository.size() << "]:\n";
        STD::function<_DataTy(size_t)> func = [&](const size_t& _ptr) { return *repository[_ptr]; };
        print(func, _Node_Format.format, repository.size());
    }
    
    // std::stack & std::priority_queue //

    // The base function for printing the contained values of std::stack and std::priority_queue.
    template <typename _Ty>
    is_printable_t<_Ty> print(const _Ty& _Top, const print_format& _Format, const size_t& _Len) {
        if (_Len == 0) {
            return;
        }
        size_t count = _Len > 1 ? 2 : 1;
        STD::initializer_list<size_t> widths;
        if (count == 1) {
            widths = { _Format.width };
        }
        else {
            widths = { _Format.width, 5 };
        }
        TAP::border_top_spliter_B(7, widths);
        STD::cout << *TAP::ver_border << STT::center("top", 7, true) << *TAP::ver_border_B;
        _Format.print_incell(_Top);
        if (count == 2) {
            STD::cout << *TAP::ver_border << STT::center("...", 5, false);
        }
        STD::cout << *TAP::ver_border << PRT::NEW_LINE;
        TAP::border_bottom(7, widths);
    }

    // Print std::stack<_Ty, _Container> where _Ty is built-in type.
    template <typename _Ty, typename _Container>
    is_built_in_t<_Ty> print(const STD::stack<_Ty, _Container>& _Stack, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        PRT::tip(_Stack, "std::stack", format.name, _Name, _Stack.size());
        print(_Stack.top(), format, _Stack.size());
    }

    // Print std::stack<_Ty, _Container> with given format.
    template <typename _Ty, typename _Container>
    is_printable_t<_Ty> print(const STD::stack<_Ty, _Container>& _Stack, const print_format& _Format, const char* _Name) {
        PRT::tip(_Stack, "std::stack", _Format.name, _Name, _Stack.size());
        print(_Stack.top(), _Format, _Stack.size());
    }

    // Print std::priority_queue<_Ty, _Container, _Pr> where _Ty is built-in type.
    template <typename _Ty, typename _Container, typename _Pr>
    is_built_in_t<_Ty> print(const STD::priority_queue<_Ty, _Container, _Pr>& _Queue, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        PRT::tip(_Queue, "std::priority_queue", format.name, _Name, _Queue.size());
        print(_Queue.top(), format, _Queue.size());
    }

    // Print std::priority_queue<_Ty, _Container, _Pr> with given format.
    template <typename _Ty, typename _Container, typename _Pr>
    is_printable_t<_Ty> print(const STD::priority_queue<_Ty, _Container, _Pr>& _Queue, const print_format& _Format, const char* _Name) {
        PRT::tip(_Queue, "std::priority_queue", _Format.name, _Name, _Queue.size());
        print(_Queue.top(), _Format, _Queue.size());
    }

    // std::queue //

    // The base function for printing the contained values of std::queue.
    template <typename _Ty, typename _Container>
    is_printable_t<_Ty> print(const STD::queue<_Ty, _Container>& _Queue, const print_format& _Format) {
        if (_Queue.size() == 0) {
            return;
        }
        size_t count = _Queue.size() > 2 ? 3 : _Queue.size();
        STD::initializer_list<size_t> widths;
        if (count == 1) {
            widths = { _Format.width };
        }
        else if (count == 2) {
            widths = { _Format.width, _Format.width };
        }
        else if (count == 3) {
            widths = { _Format.width, 5 , _Format.width };
        }
        TAP::border_top_spliter_B(7, widths);
        STD::cout << *TAP::ver_border << STT::center("front", 7, true) << *TAP::ver_border_B;
        _Format.print_incell(_Queue.front());
        if (count == 3) {
            STD::cout << *TAP::ver_border << STT::center("...", 5, false);
        }
        if (count > 1) {
            STD::cout << *TAP::ver_border;
            _Format.print_incell(_Queue.back());
        }
        STD::cout << *TAP::ver_border << PRT::NEW_LINE;
        TAP::border_bottom(7, widths);
    }

    // Print std::queue<_Ty, _Container> where _Ty is built-in type.
    template <typename _Ty, typename _Container>
    is_built_in_t<_Ty> print(const STD::queue<_Ty, _Container>& _Queue, const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        PRT::tip(_Queue, "std::queue", format.name, _Name, _Queue.size());
        print(_Queue, format);
    }

    // Print std::queue<_Ty, _Container> with given format.
    template <typename _Ty, typename _Container>
    is_printable_t<_Ty> print(const STD::queue<_Ty, _Container>& _Queue, const print_format& _Format, const char* _Name) {
        PRT::tip(_Queue, "std::queue", _Format.name, _Name, _Queue.size());
        print(_Queue, _Format);
    }

    // maps in STL //

    // The base function for printing the contained values of std::map and std::multimap.
    template <typename _Kty, typename _Vty>
    are_printable_t<_Kty, _Vty> print(const STD::function<STD::pair<_Kty, _Vty>()>& _Pair_Func, const print_format& _Format_K, const print_format& _Format_V, const size_t& _Len) {
        if (_Len == 0) {
            return;
        }
        STD::initializer_list<size_t> widths = { _Format_K.width, _Format_V.width };
        TAP::border_top(3, widths);
        STD::cout << *TAP::ver_border << ' ' << '\\' << ' ' << *TAP::ver_border << STT::center("key", _Format_K.width, true) << *TAP::ver_border;
        STD::cout << STT::center("value", _Format_V.width, true) << *TAP::ver_border << PRT::NEW_LINE;
        STD::cout << *TAP::middle_left << STT::duplicate(*TAP::hor_border, 3);
        STD::cout << *TAP::left_corner << STT::duplicate(*TAP::hor_border_B, _Format_K.width);
        STD::cout << *TAP::middle_corner << STT::duplicate(*TAP::hor_border_B, _Format_V.width);
        STD::cout << *TAP::right_corner << PRT::NEW_LINE;
        for (size_t row = 0; row < _Len; row++) {
            if (row > 0) {
                TAP::border_middle(3, widths);
            }
            STD::cout << *TAP::ver_border << STT::center(row + 1, 3, true) << *TAP::ver_border_B;
            STD::pair<_Kty, _Vty> pair = _Pair_Func();
            _Format_K.print_incell(pair.first);
            STD::cout << *TAP::ver_border;
            _Format_V.print_incell(pair.second);
            STD::cout << *TAP::ver_border << PRT::NEW_LINE;
        }
        TAP::border_bottom(3, widths);
    }

    // std::map //

    // Print std::map<_Kty, _Vty, _Pr> where _Kty and _Vty are both built-in types.
    template <typename _Kty, typename _Vty, typename _Pr>
    are_built_in_t<_Kty, _Vty> print(const STD::map<_Kty, _Vty, _Pr>& _Map, const char* _Name) {
        print_format& format_k = get_built_in_format<_Kty>();
        print_format& format_v = get_built_in_format<_Vty>();
        PRT::tip(_Map, "std::map", format_k.name, format_v.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, format_k, format_v, _Map.size());
    }

    // Print std::map<_Kty, _Vty, _Pr> where _Kty is built-in type.
    template <typename _Kty, typename _Vty, typename _Pr>
    partly_built_in<_Kty, _Vty> print(const STD::map<_Kty, _Vty, _Pr>& _Map, const print_format& _Format_V, const char* _Name) {
        print_format& format_k = get_built_in_format<_Kty>();
        PRT::tip(_Map, "std::map", format_k.name, _Format_V.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, format_k, _Format_V, _Map.size());
    }

    // Print std::map<_Kty, _Vty, _Pr> where _Vty is built-in type.
    template <typename _Kty, typename _Vty, typename _Pr>
    partly_built_in<_Vty, _Kty> print(const STD::map<_Kty, _Vty, _Pr>& _Map, const print_format& _Format_K, const char* _Name) {
        print_format& format_v = get_built_in_format<_Vty>();
        PRT::tip(_Map, "std::map", _Format_K.name, format_v.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, _Format_K, format_v, _Map.size());
    }

    // Print std::map<_Kty, _Vty, _Pr> with given formats.
    template <typename _Kty, typename _Vty, typename _Pr>
    are_printable_t<_Vty, _Kty> print(const STD::map<_Kty, _Vty, _Pr>& _Map, const print_format& _Format_K, const print_format& _Format_V, const char* _Name) {
        PRT::tip(_Map, "std::map", _Format_K.name, _Format_V.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, _Format_K, _Format_V, _Map.size());
    }

    // Print std::map<_Kty, _Vty, _Pr, _Alloc> with given formats and function to get std::pair<_Kty, _Vty>.
    template <typename _Kty, typename _Vty, typename _Pr, typename _Alloc>
    are_printable_t<_Vty, _Kty> print(const STD::map<_Kty, _Vty, _Pr, _Alloc>& _Map, const print_format& _Format_K, const print_format& _Format_V,
        const STD::function<STD::pair<_Kty, _Vty>(typename STD::map<_Kty, _Vty>::const_iterator)>& _Val_Func, const char* _Name) {
        PRT::tip(_Map, "std::map", _Format_K.name, _Format_V.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return _Val_Func(*iter++); };
        print(func, _Format_K, _Format_V, _Map.size());
    }

    // std::multimap //

    // Print std::multimap<_Kty, _Vty, _Pr> where _Kty and _Vty are both built-in types.
    template <typename _Kty, typename _Vty, typename _Pr>
    are_built_in_t<_Kty, _Vty> print(const STD::multimap<_Kty, _Vty, _Pr>& _Map, const char* _Name) {
        print_format& format_k = get_built_in_format<_Kty>();
        print_format& format_v = get_built_in_format<_Vty>();
        PRT::tip(_Map, "std::multimap", format_k.name, format_v.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, format_k, format_v, _Map.size());
    }

    // Print std::multimap<_Kty, _Vty, _Pr> where _Kty is built-in type.
    template <typename _Kty, typename _Vty, typename _Pr>
    partly_built_in<_Kty, _Vty> print(const STD::multimap<_Kty, _Vty, _Pr>& _Map, const print_format& _Format_V, const char* _Name) {
        print_format& format_k = get_built_in_format<_Kty>();
        PRT::tip(_Map, "std::multimap", format_k.name, _Format_V.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, format_k, _Format_V, _Map.size());
    }

    // Print std::multimap<_Kty, _Vty, _Pr> where _Vty is built-in type.
    template <typename _Kty, typename _Vty, typename _Pr>
    partly_built_in<_Vty, _Kty> print(const STD::multimap<_Kty, _Vty, _Pr>& _Map, const print_format& _Format_K, const char* _Name) {
        print_format& format_v = get_built_in_format<_Vty>();
        PRT::tip(_Map, "std::multimap", _Format_K.name, format_v.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, _Format_K, format_v, _Map.size());
    }

    // Print std::multimap<_Kty, _Vty, _Pr> with given formats.
    template <typename _Kty, typename _Vty, typename _Pr>
    are_printable_t<_Kty, _Vty> print(const STD::multimap<_Kty, _Vty, _Pr>& _Map, const print_format& _Format_K, const print_format& _Format_V, const char* _Name) {
        PRT::tip(_Map, "std::multimap", _Format_K.name, _Format_V.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, _Format_K, _Format_V, _Map.size());
    }

    // Print std::multimap<_Kty, _Vty, _Pr, _Alloc> with given formats and function to get std::pair<_Kty, _Vty>.
    template <typename _Kty, typename _Vty, typename _Pr, typename _Alloc>
    are_printable_t<_Kty, _Vty> print(const STD::multimap<_Kty, _Vty, _Pr, _Alloc>& _Map, const print_format& _Format_K, const print_format& _Format_V,
        const STD::function<STD::pair<_Kty, _Vty>(typename STD::multimap<_Kty, _Vty, _Pr, _Alloc>::const_iterator)>& _Val_Func, const char* _Name) {
        PRT::tip(_Map, "std::multimap", _Format_K.name, _Format_V.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return _Val_Func(*iter++); };
        print(func, _Format_K, _Format_V, _Map.size());
    }

    // std::unordered_map //

    // Print std::unordered_map<_Kty, _Vty, _Hasher, _Keyeq> where _Kty and _Vty are both built-in types.
    template <typename _Kty, typename _Vty, typename _Hasher, typename _Keyeq>
    are_built_in_t<_Kty, _Vty> print(const STD::unordered_map<_Kty, _Vty, _Hasher, _Keyeq>& _Map, const char* _Name) {
        print_format& format_k = get_built_in_format<_Kty>();
        print_format& format_v = get_built_in_format<_Vty>();
        PRT::tip(_Map, "std::unordered_map", format_k.name, format_v.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, format_k, format_v, _Map.size());
    }

    // Print std::unordered_map<_Kty, _Vty, _Hasher, _Keyeq> where _Kty is built-in type.
    template <typename _Kty, typename _Vty, typename _Hasher, typename _Keyeq>
    partly_built_in<_Kty, _Vty> print(const STD::unordered_map<_Kty, _Vty, _Hasher, _Keyeq>& _Map, const print_format& _Format_V, const char* _Name) {
        print_format& format_k = get_built_in_format<_Kty>();
        PRT::tip(_Map, "std::unordered_map", format_k.name, _Format_V.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, format_k, _Format_V, _Map.size());
    }

    // Print std::unordered_map<_Kty, _Vty, _Hasher, _Keyeq> where _Vty is built-in type.
    template <typename _Kty, typename _Vty, typename _Hasher, typename _Keyeq>
    partly_built_in<_Vty, _Kty> print(const STD::unordered_map<_Kty, _Vty, _Hasher, _Keyeq>& _Map, const print_format& _Format_K, const char* _Name) {
        print_format& format_v = get_built_in_format<_Vty>();
        PRT::tip(_Map, "std::unordered_map", _Format_K.name, format_v.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, _Format_K, format_v, _Map.size());
    }

    // Print std::unordered_map<_Kty, _Vty, _Hasher, _Keyeq> with given formats.
    template <typename _Kty, typename _Vty, typename _Hasher, typename _Keyeq>
    are_printable_t<_Kty, _Vty> print(const STD::unordered_map<_Kty, _Vty, _Hasher, _Keyeq>& _Map, const print_format& _Format_K, const print_format& _Format_V, const char* _Name) {
        PRT::tip(_Map, "std::unordered_map", _Format_K.name, _Format_V.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, _Format_K, _Format_V, _Map.size());
    }

    // Print std::unordered_map<_Kty, _Vty, _Hasher, _Keyeq, _Alloc> with given formats and function to get std::pair<_Kty, _Vty>.
    template <typename _Kty, typename _Vty, typename _Hasher, typename _Keyeq, typename _Alloc>
    are_printable_t<_Kty, _Vty> print(const STD::unordered_map<_Kty, _Vty, _Hasher, _Keyeq, _Alloc>& _Map, const print_format& _Format_K, const print_format& _Format_V,
        const STD::function<STD::pair<_Kty, _Vty>(typename STD::unordered_map<_Kty, _Vty, _Hasher, _Keyeq, _Alloc>::const_iterator)> _Val_Func, const char* _Name) {
        PRT::tip(_Map, "std::unordered_map", _Format_K.name, _Format_V.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return _Val_Func(*iter++); };
        print(func, _Format_K, _Format_V, _Map.size());
    }

    // std::unordered_map //

    // Print std::unordered_multimap<_Kty, _Vty, _Hasher, _Keyeq> where _Kty and _Vty are both built-in types.
    template <typename _Kty, typename _Vty, typename _Hasher, typename _Keyeq>
    are_built_in_t<_Kty, _Vty> print(const STD::unordered_multimap<_Kty, _Vty, _Hasher, _Keyeq>& _Map, const char* _Name) {
        print_format& format_k = get_built_in_format<_Kty>();
        print_format& format_v = get_built_in_format<_Vty>();
        PRT::tip(_Map, "std::unordered_multimap", format_k.name, format_v.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, format_k, format_v, _Map.size());
    }

    // Print std::unordered_multimap<_Kty, _Vty, _Hasher, _Keyeq> where _Kty is built-in type.
    template <typename _Kty, typename _Vty, typename _Hasher, typename _Keyeq>
    partly_built_in<_Kty, _Vty> print(const STD::unordered_multimap<_Kty, _Vty, _Hasher, _Keyeq>& _Map, const print_format& _Format_V, const char* _Name) {
        print_format& format_k = get_built_in_format<_Kty>();
        PRT::tip(_Map, "std::unordered_multimap", format_k.name, _Format_V.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, format_k, _Format_V, _Map.size());
    }

    // Print std::unordered_multimap<_Kty, _Vty, _Hasher, _Keyeq> where _Vty is built-in type.
    template <typename _Kty, typename _Vty, typename _Hasher, typename _Keyeq>
    partly_built_in<_Vty, _Kty> print(const STD::unordered_multimap<_Kty, _Vty, _Hasher, _Keyeq>& _Map, const print_format& _Format_K, const char* _Name) {
        print_format& format_v = get_built_in_format<_Vty>();
        PRT::tip(_Map, "std::unordered_multimap", _Format_K.name, format_v.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, _Format_K, format_v, _Map.size());
    }

    // Print std::unordered_multimap<_Kty, _Vty, _Hasher, _Keyeq> with givem formats.
    template <typename _Kty, typename _Vty, typename _Hasher, typename _Keyeq>
    are_printable_t<_Kty, _Vty> print(const STD::unordered_multimap<_Kty, _Vty, _Hasher, _Keyeq>& _Map, const print_format& _Format_K, const print_format& _Format_V, const char* _Name) {
        PRT::tip(_Map, "std::unordered_multimap", _Format_K.name, _Format_V.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return *iter++; };
        print(func, _Format_K, _Format_V, _Map.size());
    }

    // Print std::unordered_multimap<_Kty, _Vty, _Hasher, _Keyeq> with given formats and function to get std::pair<_Kty, _Vty>.
    template <typename _Kty, typename _Vty, typename _Hasher, typename _Keyeq, typename _Alloc>
    are_printable_t<_Kty, _Vty> print(const STD::unordered_multimap<_Kty, _Vty, _Hasher, _Keyeq, _Alloc>& _Map, const print_format& _Format_K, const print_format& _Format_V,
        const STD::function<STD::pair<_Kty, _Vty>(typename STD::unordered_multimap<_Kty, _Vty, _Hasher, _Keyeq, _Alloc>::const_iterator)> _Val_Func, const char* _Name) {
        PRT::tip(_Map, "std::unordered_multimap", _Format_K.name, _Format_V.name, _Name, _Map.size());
        auto iter = _Map.begin();
        STD::function<STD::pair<_Kty, _Vty>()> func = [&]() -> STD::pair<_Kty, _Vty> { return _Val_Func(*iter++); };
        print(func, _Format_K, _Format_V, _Map.size());
    }

    // Here comes the slope for printing one-dimensional-array-like value.

    // The base function for printing a chart whose cells are filled with values.
    template <typename _Ty>
    is_printable_t<_Ty> print(_Ty** const _Ptr, const print_format& _Format, const size_t& _Row, const size_t& _Col) {
        for (size_t charts_c = 0; charts_c < PRT::ceil_divide(_Col, _Format.length); charts_c++) {
            size_t end_c  = STD::min((charts_c + 1) * _Format.length, _Col);
            size_t length = STD::min(_Col - charts_c * _Format.length, _Format.length);
            for (size_t charts_r = 0; charts_r < PRT::ceil_divide(_Row, PRT::_Max_rows); charts_r++) {
                TAP::border_top(length, _Format.width, 3);
                STD::cout << *TAP::ver_border << ' ' << '\\' << ' ' << *TAP::ver_border;
                for (size_t col = charts_c * _Format.length; col < end_c; col++) {
                    STD::cout << STT::center(col, _Format.width, true) << *TAP::ver_border;
                }
                STD::cout << PRT::NEW_LINE;
                STD::cout << *TAP::middle_left << STT::duplicate(*TAP::hor_border, 3) << *TAP::left_corner;
                for (size_t col = charts_c * _Format.length; col < end_c; col++) {
                    STD::cout << STT::duplicate(*TAP::hor_border_B, _Format.width);
                    if (col < end_c - 1) {
                        STD::cout << *TAP::middle_corner;
                    }
                    else {
                        STD::cout << *TAP::right_corner;
                        STD::cout << PRT::NEW_LINE;
                    }
                }
                size_t end_r = STD::min((charts_r + 1) * PRT::_Max_rows, _Row);
                for (size_t row = charts_r * PRT::_Max_rows; row < end_r; row++) {
                    STD::cout << *TAP::ver_border << STT::center(row, 3, true) << *TAP::ver_border_B;
                    for (size_t col = charts_c * _Format.length; col < end_c; col++) {
                        _Format.print_incell(*((_Ty*)(_Ptr) + row * _Col + col));
                        STD::cout << *TAP::ver_border;
                    }
                    STD::cout << PRT::NEW_LINE;
                    if (row < end_r - 1) {
                        TAP::border_middle(length, _Format.width, 3);
                    }
                    else {
                        TAP::border_bottom(length, _Format.width, 3);
                    }
                }
            }
        }
    }

    // Print two-dimensional-array of built-in _Ty.
    template <typename _Ty, size_t _Row, size_t _Col>
    is_built_in_t<_Ty> print(const _Ty (&_Arr)[_Row][_Col], const char* _Name) {
        print_format& format = get_built_in_format<_Ty>();
        STD::cout << '@' << (void*)(_Arr) << ' ' << format.name << ' ' << _Name << '[' << _Row << "][" << _Col << "]:\n";
        print((_Ty**)_Arr, format, _Row, _Col);
    }

    // Print two-dimensional-array with given format.
    template <typename _Ty, size_t _Row, size_t _Col>
    is_printable_t<_Ty> print(const _Ty (&_Arr)[_Row][_Col], const print_format& _Format, const char* _Name) {
        STD::cout << '@' << (void*)(_Arr) << ' ' << _Format.name << ' ' << _Name << '[' << _Row << "][" << _Col << "]:\n";
        print((_Ty**)_Arr, _Format, _Row, _Col);
    }
}

#undef STD
#undef PRT
#undef STT
#undef TAP

#endif // _PREINTE_
#endif // __cplusplus
