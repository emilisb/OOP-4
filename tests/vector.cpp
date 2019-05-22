#include "gtest/gtest.h"
#include "../src/vector.h"
#include <vector>

typedef vector<int> vint;

TEST(Constructor, Empty)
{
    vint vec;
    EXPECT_EQ(0, vec.size());
    EXPECT_EQ(0, vec.capacity());
}

TEST(Constructor, CountAndValue)
{
    int count = 100;
    int value = 5;
    vint vec(count, value); // { 5, 5 }

    for (int i = 0; i < count; i++) {
        EXPECT_EQ(value, vec.at(i));
        EXPECT_EQ(value, vec.at(i));
    }
}

TEST(Constructor, WithIterators)
{
    vint original({ 1, 2, 3, 4 });
    vint copy(original.begin(), original.end());

    EXPECT_EQ(4, copy.size());

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(original.at(i), copy.at(i));
    }
}

TEST(Constructor, WithOtherVector)
{
    vint original({ 1, 2, 3, 4 });
    vint copy(original);

    EXPECT_EQ(4, copy.size());

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(original.at(i), copy.at(i));
    }
}

TEST(Constructor, Move)
{
    vint original({ 1, 2, 3, 4 });
    vint copy = std::move(original);

    EXPECT_EQ(4, copy.size());
    EXPECT_EQ(1, copy.at(0));
    EXPECT_EQ(2, copy.at(1));
    EXPECT_EQ(3, copy.at(2));
    EXPECT_EQ(4, copy.at(3));

    EXPECT_TRUE(original.empty());
}

TEST(Constructor, WithInitList)
{
    std::initializer_list<int> list({ 1, 2, 3, 4 });
    vint vec(list);

    EXPECT_EQ(list.size(), vec.size());

    for (int i = 0; i < list.size(); i++) {
        EXPECT_EQ(*(list.begin() + i), vec.at(i));
    }
}

TEST(Deconstructor, FreeMemory)
{
    vint vec;
    vec.~vector();

    EXPECT_EQ(nullptr, vec.data());
}

TEST(Operator, AssignToOtherVector)
{
    vint original({ 1, 2, 3, 4 });
    vint copy;
    copy = original;
    EXPECT_EQ(4, copy.size());

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(original.at(i), copy.at(i));
    }
}

TEST(Function, Assign)
{
    int count = 3;
    int value = 5;
    vint vec({ 1, 2, 3, 4 });
    vec.assign(count, value);

    EXPECT_EQ(count, vec.size());
    for (int i = 0; i < vec.size(); i++) {
        EXPECT_EQ(value, vec.at(i));
    }
}

TEST(Function, AssignWithIterator)
{
    vint original({ 10, 20, 30, 40, 50 });
    vint vec({ 1, 2, 3, 4 });
    vec.assign(original.begin(), original.end());

    EXPECT_EQ(5, vec.size());
    EXPECT_EQ(10, vec.at(0));
    EXPECT_EQ(20, vec.at(1));
    EXPECT_EQ(30, vec.at(2));
    EXPECT_EQ(40, vec.at(3));
    EXPECT_EQ(50, vec.at(4));
}

TEST(Access, At)
{
    vint vec({ 1, 2, 3, 4 });
    
    EXPECT_EQ(vec.at(0), 1);
    EXPECT_EQ(vec.at(1), 2);
    EXPECT_EQ(vec.at(2), 3);
    EXPECT_EQ(vec.at(3), 4);
    
    EXPECT_THROW(vec.at(10), std::out_of_range);
}

TEST(Access, OperatorArray)
{
    vint vec({ 1, 2, 3, 4 });

    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(2, vec[1]);
    EXPECT_EQ(3, vec[2]);
    EXPECT_EQ(4, vec[3]);
}

TEST(Access, front)
{
    vint vec({ 1, 2, 3, 4 });
    EXPECT_EQ(1, vec.front());
}

TEST(Access, back)
{
    vint vec({ 1, 2, 3, 4 });
    EXPECT_EQ(4, vec.back());
}

TEST(Access, Data)
{
    vint vec({ 1, 2, 3, 4 });
    int *data = vec.data();

    EXPECT_EQ(1, data[0]);
    EXPECT_EQ(2, data[1]);
    EXPECT_EQ(3, data[2]);
    EXPECT_EQ(4, data[3]);
}

TEST(Iterators, Begin)
{
    vint vec({ 1, 2, 3, 4 });
    EXPECT_EQ(1, *vec.begin());
}

TEST(Iterators, End)
{
    vint vec({ 1, 2, 3, 4 });
    EXPECT_EQ(vec.begin() + vec.size(), vec.end());
}

TEST(Iterators, Rbegin)
{
    vint vec({ 1, 2, 3, 4 });
    EXPECT_EQ(4, *vec.rbegin());
}

TEST(Iterators, Rend)
{
    vint vec({ 1, 2, 3, 4 });
    EXPECT_EQ(1, *(vec.rend() - 1));
}

TEST(Modifier, Erase)
{
    vint vec({ 1, 2, 3, 4 });
    vec.erase(vec.begin() + 1);
    
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec.at(0), 1);
    EXPECT_EQ(vec.at(1), 3);
    EXPECT_EQ(vec.at(2), 4);
}

TEST(Modifier, EraseWithRange)
{
    vint vec({ 1, 2, 3, 4 });
    vec.erase(vec.begin() + 1, vec.begin() + 3);
    
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.at(0), 1);
    EXPECT_EQ(vec.at(1), 4);
}

TEST(Modifier, PushBack)
{
    vint vec;
    vec.push_back(9);

    EXPECT_EQ(9, vec.at(0));
}

TEST(Modifier, PushBackMove)
{
    vint vec;
    int value = 5;
    vec.push_back(std::move(value));

    EXPECT_EQ(5, vec.at(0));
}

TEST(Modifier, EmplaceBack)
{
    struct T {
        int a;
        double b;
        std::string c;
        
        T(int a, double b, std::string &&c) : a(a) , b(b), c(std::move(c)) {}
    };
    
    vector<T> objects;
    objects.emplace_back(42, 3.14, "foo");
    
    EXPECT_EQ(1, objects.size());
    EXPECT_EQ(42, objects.at(0).a);
    EXPECT_EQ(3.14, objects.at(0).b);
    EXPECT_EQ("foo", objects.at(0).c);
}

TEST(Capacity, Empty)
{
    vint vec;
    EXPECT_TRUE(vec.empty());

    vec.push_back(1);
    EXPECT_FALSE(vec.empty());
}

TEST(Capacity, Size)
{
    vint vec({ 1, 2, 3, 4 });
    EXPECT_EQ(4, vec.size());
}

TEST(Capacity, Reserve)
{
    vint vec;
    vec.reserve(100);

    EXPECT_EQ(100, vec.capacity());
}

TEST(Capacity, ShrinkToFit)
{
    vint vec({ 1, 2, 3, 4 });
    vec.reserve(100); // TODO change to resize
    vec.shrink_to_fit();
    EXPECT_EQ(4, vec.capacity());
}

TEST(Modifier, Clear)
{
    vint vec({ 1, 2, 3, 4 });
    vec.clear();

    EXPECT_EQ(0, vec.size());
}

TEST(Modifier, InsertWithValue)
{
    int value = 5;
    vint vec({ 1, 2, 3, 4 });
    auto it = vec.insert(vec.begin(), value);
    
    EXPECT_EQ(5, vec.size());
    EXPECT_EQ(5, *it);
    EXPECT_EQ(5, vec.at(0));
    for (int i = 1; i < 5; i++) {
        EXPECT_EQ(i, vec.at(i));
    }

    it = vec.insert(vec.end(), value);
    EXPECT_EQ(6, vec.size());
    EXPECT_EQ(5, *it);
    EXPECT_EQ(5, vec.at(5));
}

TEST(Modifier, InsertWithValueMove)
{
    int value = 5;
    vint vec({ 1, 2, 3, 4 });
    auto it = vec.insert(vec.begin(), std::move(value));

    EXPECT_EQ(5, vec.size());
    EXPECT_EQ(5, *it);
    EXPECT_EQ(5, vec.at(0));
    for (int i = 1; i < 5; i++) {
        EXPECT_EQ(i, vec.at(i));
    }
}

TEST(Modifier, InsertWithCount)
{
    vint vec({ 1, 2, 3, 4 });
    auto it = vec.insert(vec.begin(), 3, 5);

    EXPECT_EQ(7, vec.size());
    EXPECT_EQ(5, *it);
    
    EXPECT_EQ(5, vec.at(0));
    EXPECT_EQ(5, vec.at(1));
    EXPECT_EQ(5, vec.at(2));
   
    EXPECT_EQ(1, vec.at(3));
    EXPECT_EQ(2, vec.at(4));
    EXPECT_EQ(3, vec.at(5));
    EXPECT_EQ(4, vec.at(6));
}

TEST(Modifier, Emplace)
{
    struct T {
        int a;
        double b;
        std::string c;
        
        T(int a, double b, std::string &&c) : a(a) , b(b), c(std::move(c)) {}
    };
    
    vector<T> objects;
    objects.emplace(objects.begin(), 42, 3.14, "foo");
    
    EXPECT_EQ(1, objects.size());
    EXPECT_EQ(42, objects.at(0).a);
    EXPECT_EQ(3.14, objects.at(0).b);
    EXPECT_EQ("foo", objects.at(0).c);
}

TEST(Modifier, PopBack)
{
    vint vec({ 1, 2, 3, 4 });
    int result[3] = { 1, 2, 3 };
    vec.pop_back();

    EXPECT_EQ(3, vec.size());

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(result[i], vec.at(i));
    }
}

TEST(Modifier, Resize)
{
    vint vec({ 1, 2, 3, 4 });
    vec.resize(10);

    EXPECT_EQ(10, vec.size());
    EXPECT_EQ(1, vec.at(0));
    EXPECT_EQ(2, vec.at(1));
    EXPECT_EQ(3, vec.at(2));
    EXPECT_EQ(4, vec.at(3));
    for (int i = 5; i < 10; i++) {
        EXPECT_EQ(0, vec.at(i));
    }

    vec.resize(2);
    EXPECT_EQ(2, vec.size());
    EXPECT_EQ(1, vec.at(0));
    EXPECT_EQ(2, vec.at(1));
}

TEST(Modifier, ResizeWithValue)
{
    vint vec({ 1, 2, 3, 4 });
    vec.resize(10, 999);

    EXPECT_EQ(10, vec.size());
    EXPECT_EQ(1, vec.at(0));
    EXPECT_EQ(2, vec.at(1));
    EXPECT_EQ(3, vec.at(2));
    EXPECT_EQ(4, vec.at(3));
    for (int i = 5; i < 10; i++) {
        EXPECT_EQ(999, vec.at(i));
    }

    vec.resize(2);
    EXPECT_EQ(2, vec.size());
    EXPECT_EQ(1, vec.at(0));
    EXPECT_EQ(2, vec.at(1));
}

TEST(Modifier, Swap)
{
    vint vec({ 1, 2, 3, 4 });
    vint other({ 10, 20, 30, 40, 50 });
    vec.swap(other);

    EXPECT_EQ(5, vec.size());
    EXPECT_EQ(4, other.size());

    for (int i = 0; i < 5; i++) {
        EXPECT_EQ((i + 1) * 10, vec.at(i));
    }

    for (int i = 0; i < 4; i++) {
        EXPECT_EQ(i + 1, other.at(i));
    }
}

TEST(Operator, Equal)
{
    vint vec({ 1, 2, 3, 4 });
    vint other({ 1, 2, 3, 4 });
    vint different({ 1, 2, 3, 5 });
    
    EXPECT_TRUE(vec == other);
    EXPECT_FALSE(vec == different);
}

TEST(Operator, NotEqual)
{
    vint vec({ 1, 2, 3, 4 });
    vint other({ 1, 2, 3, 4 });
    vint different({ 1, 2, 3, 5 });
    
    EXPECT_FALSE(vec != other);
    EXPECT_TRUE(vec != different);
}

TEST(Operator, Less)
{
    vint vec({ 1, 2, 3, 4 });
    vint other({ 1, 2, 3, 4 });
    vint different({ 1, 3, 3, 4 });
    
    EXPECT_FALSE(vec < other);
    EXPECT_TRUE(vec < different);
}

TEST(Operator, More)
{
    vint vec({ 1, 2, 3, 4 });
    vint other({ 1, 2, 3, 4 });
    vint different({ 1, 3, 3, 4 });
    
    EXPECT_FALSE(vec > other);
    EXPECT_FALSE(vec > different);
}

TEST(Operator, LessOrEqual)
{
    vint vec({ 1, 2, 3, 4 });
    vint other({ 1, 2, 3, 4 });
    vint different({ 1, 3, 3, 4 });
    
    EXPECT_TRUE(vec <= other);
    EXPECT_TRUE(vec <= different);
}

TEST(Operator, MoreOrEqual)
{
    vint vec({ 1, 2, 3, 4 });
    vint other({ 1, 2, 3, 4 });
    vint different({ 1, 3, 3, 4 });
    
    EXPECT_TRUE(vec >= other);
    EXPECT_FALSE(vec >= different);
}
