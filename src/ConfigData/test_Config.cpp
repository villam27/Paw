#include "gtest/gtest.h"
#include <Config.h>

class ConfigTest : public ::testing::Test {
    protected:
        ConfigTest() {
            _config = new Config();
        }

        ~ConfigTest() override {
            delete _config;
        }

        Config *_config;
};

TEST_F(ConfigTest, LoadAll) {
    EXPECT_TRUE(_config->LoadAll());
}

TEST_F(ConfigTest, CheckAppData) {
    const AppData *appData = _config->GetAppData();

    ASSERT_TRUE(_config->LoadAppData());
    EXPECT_EQ(appData->fps, 30);
    EXPECT_EQ(appData->scale, 3);
}

TEST_F(ConfigTest, CheckSheets) {
    const std::vector<Sheet> *sheets = _config->GetSheets();

    ASSERT_TRUE(_config->LoadSheets());
    EXPECT_EQ(sheets->size(), 1);
}

TEST_F(ConfigTest, CheckAnimations) {
    const std::unordered_map<std::string, Animation> *animations = _config->GetAnimation();

    ASSERT_TRUE(_config->LoadAnimation());
    EXPECT_EQ(animations->size(), 4);
}