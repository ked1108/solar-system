#include <gtest/gtest.h>
#include "body.h"
#include "raylib.h"

TEST(PlanetTest, Get) {
    Body p({0, 0, 0}, 10.0f, RED, 10);
    // EXPECT_EQ(p.get_color(), (RED));
    EXPECT_EQ(p.get_pos().x, 0.0f);
    EXPECT_EQ(p.get_pos().y, 0.0f);
    EXPECT_EQ(p.get_pos().z, 0.0f);
    EXPECT_EQ(p.get_radius(), 10.0f);
}