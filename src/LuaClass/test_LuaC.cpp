#include "gtest/gtest.h"
#include "LuaC.h"

class LuaCTest : public ::testing::Test {
    protected:
        LuaC *luaC;

        virtual void SetUp() {
            luaC = new LuaC();
        }

        virtual void TearDown() {
            delete luaC;
        }
};

TEST_F(LuaCTest, Basic) {
    ASSERT_NE(luaC->GetLuaState(), (lua_State *)NULL);
}

TEST_F(LuaCTest, MemoryLoad) {
    EXPECT_TRUE(luaC->LoadScriptFromMemory("print(\"Hello World!\")"));
}

TEST_F(LuaCTest, FileLoad) {
    //  data folder must be in the same directory as the executable
    EXPECT_TRUE(luaC->LoadScript("data/script.lua"));
}