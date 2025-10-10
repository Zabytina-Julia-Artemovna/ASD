// Copyright 2025 Julia Zabytina
#include <gtest/gtest.h>
#include "../lib_circle/circle.h"
#include "../lib_sphere/sphere.h"

/*
TEST(TestCircleLib, circle_constructor_of_initialization1) {
    // Arrange & Act
    Circle circle(1, 1, 5);
    // Assert
    EXPECT_EQ(circle.getX(), 1);
    EXPECT_EQ(circle.getY(), 1);
    EXPECT_EQ(circle.getR(), 5);
}
TEST(TestCircleLib, circle_constructor_of_initialization2) {
    // Arrange & Act
    Circle circle(Point(1, 1), 5);
    // Assert
    EXPECT_EQ(circle.getX(), 1);
    EXPECT_EQ(circle.getY(), 1);
    EXPECT_EQ(circle.getR(), 5);
}
TEST(TestCircleLib, circle_copy_constructor) {
    // Arrange & Act
    Circle circle1(Point(1, 1), 5);
    Circle circle2(circle1);
    // Assert
    EXPECT_TRUE(circle1 == circle2);
}
TEST(TestCircleLib, circle_equal_operator_expect_true) {
    // Arrange & Act
    Circle circle1(1, 2, 4);
    Circle circle2(1, 2, 4);
    Circle circle3(5, 6, 8);
    // Assert
    EXPECT_TRUE(circle1 == circle2);
}
TEST(TestCircleLib, circle_equal_operator_expect_false) {
    // Arrange & Act
    Circle circle1(1, 2, 4);
    Circle circle2(1, 2, 4);
    Circle circle3(5, 6, 8);
    // Assert
    EXPECT_FALSE(circle1 == circle3);
}
TEST(TestCircleLib, circle_not_equal_operator_expect_true) {
    // Arrange & Act
    Circle circle1(1, 2, 4);
    Circle circle2(1, 2, 4);
    Circle circle3(5, 6, 8);
    // Assert
    EXPECT_TRUE(circle1 != circle3);
}
TEST(TestCircleLib, circle_not_equal_operator_expect_false) {
    // Arrange & Act
    Circle circle1(1, 2, 4);
    Circle circle2(1, 2, 4);
    Circle circle3(5, 6, 8);
    // Assert
    EXPECT_FALSE(circle1 != circle2);
}
TEST(TestSphereLib, sphere_constructor_of_initialization1) {
    // Arrange & Act
    Sphere sphere(2, 3, 5, 7);
    // Assert
    EXPECT_EQ(sphere.getX(), 2);
    EXPECT_EQ(sphere.getY(), 3);
    EXPECT_EQ(sphere.getZ(), 5);
    EXPECT_EQ(sphere.getR(), 7);
}
TEST(TestSphereLib, sphere_constructor_of_initialization2) {
    // Arrange & Act
    Sphere sphere(Point3D(2, 8, 9), 3);
    // Assert
    EXPECT_EQ(sphere.getX(), 2);
    EXPECT_EQ(sphere.getY(), 8);
    EXPECT_EQ(sphere.getZ(), 9);
    EXPECT_EQ(sphere.getR(), 3);
}
TEST(TestSphereLib, sphere_copy_constructor) {
    // Arrange & Act
    Sphere sphere1(Point3D(1, 1, 1), 5);
    Sphere sphere2(sphere1);
    // Assert
    EXPECT_TRUE(sphere1 == sphere2);
}
TEST(TestSphereLib, sphere_equal_operator_expect_true) {
    // Arrange & Act
    Sphere sphere1(1, 2, 2, 4);
    Sphere sphere2(1, 2, 2, 4);
    Sphere sphere3(5, 6, 6, 8);
    // Assert
    EXPECT_TRUE(sphere1 == sphere2);
}
TEST(TestSphereLib, sphere_equal_operator_expect_false) {
    // Arrange & Act
    Sphere sphere1(1, 2, 2, 4);
    Sphere sphere2(1, 2, 2, 4);
    Sphere sphere3(5, 6, 6, 8);
    // Assert
    EXPECT_FALSE(sphere1 == sphere3);
}
TEST(TestSphereLib, sphere_not_equal_operator_expect_true) {
    // Arrange & Act
    Sphere sphere1(1, 2, 2, 4);
    Sphere sphere2(1, 2, 2, 4);
    Sphere sphere3(5, 6, 6, 8);
    // Assert
    EXPECT_TRUE(sphere1 != sphere3);
}
TEST(TestSphereLib, sphere_not_equal_operator_expect_false) {
    // Arrange & Act
    Sphere sphere1(1, 2, 2, 4);
    Sphere sphere2(1, 2, 2, 4);
    Sphere sphere3(5, 6, 6, 8);
    // Assert
    EXPECT_FALSE(sphere1 != sphere2);
}
TEST(TestPointLib, point_constructor_of_initialization) {
    // Arrange & Act
    Point point(5, 5);
    // Assert
    EXPECT_EQ(point.getX(), 5);
    EXPECT_EQ(point.getY(), 5);
}
TEST(TestPointLib, point_default_constructor) {
    // Arrange & Act
    Point point;
    // Assert
    EXPECT_EQ(point.getX(), 0);
    EXPECT_EQ(point.getY(), 0);
}
TEST(TestPointLib, point_copy_constructor) {
    // Arrange & Act
    Point point1(2, 3);
    Point point2(point1);
    // Assert
    EXPECT_TRUE(point1 == point2);
}
TEST(TestPointLib, point_equal_operator_expect_true) {
    // Arrange & Act
    Point point1(1, 2);
    Point point2(1, 2);
    Point point3(5, 6);
    // Assert
    EXPECT_TRUE(point1 == point2);
}
TEST(TestPointLib, point_equal_operator_expect_false) {
    // Arrange & Act
    Point point1(1, 2);
    Point point2(1, 2);
    Point point3(5, 6);
    // Assert
    EXPECT_FALSE(point1 == point3);
}
TEST(TestPointLib, point_not_equal_operator_expect_true) {
    // Arrange & Act
    Point point1(1, 2);
    Point point2(1, 2);
    Point point3(5, 6);
    // Assert
    EXPECT_TRUE(point1 != point3);
}
TEST(TestPointLib, point_not_equal_operator_expect_false) {
    // Arrange & Act
    Point point1(1, 2);
    Point point2(1, 2);
    Point point3(5, 6);
    // Assert
    EXPECT_FALSE(point1 != point2);
}
TEST(TestPointLib, get_distance_to) {
    // Arrange & Act
    Point point1(1, 2);
    Point point2(5, 6);
    // Assert
    EXPECT_EQ(point1.getDistanceTo(point2), 6);
}
TEST(TestPoint3DLib, point3d_constructor_of_initialization) {
    // Arrange & Act
    Point3D point(5, 5, 7);
    // Assert
    EXPECT_EQ(point.getX(), 5);
    EXPECT_EQ(point.getY(), 5);
    EXPECT_EQ(point.getZ(), 7);
}
TEST(TestPoint3DLib, point3d_default_constructor) {
    // Arrange & Act
    Point3D point;
    // Assert
    EXPECT_EQ(point.getX(), 0);
    EXPECT_EQ(point.getY(), 0);
    EXPECT_EQ(point.getZ(), 0);
}
TEST(TestPoint3DLib, point3d_copy_constructor) {
    // Arrange & Act
    Point3D point1(5, 5, 7);
    Point3D point2(point1);
    // Assert
    EXPECT_TRUE(point1 == point2);
}
TEST(TestPoint3DLib, point3d_equal_operator_expect_true) {
    // Arrange & Act
    Point3D point1(1, 2, 2);
    Point3D point2(1, 2, 2);
    Point3D point3(5, 6, 6);
    // Assert
    EXPECT_TRUE(point1 == point2);
}
TEST(TestPoint3DLib, point3d_equal_operator_expect_false) {
    // Arrange & Act
    Point3D point1(1, 2, 2);
    Point3D point2(1, 2, 2);
    Point3D point3(5, 6, 6);
    // Assert
    EXPECT_FALSE(point1 == point3);
}
TEST(TestPoint3DLib, point3d_not_equal_operator_expect_true) {
    // Arrange & Act
    Point3D point1(1, 2, 2);
    Point3D point2(1, 2, 2);
    Point3D point3(5, 6, 6);
    // Assert
    EXPECT_TRUE(point1 != point3);
}
TEST(TestPoint3DLib, point3d_not_equal_operator_expect_false) {
    // Arrange & Act
    Point3D point1(1, 2, 2);
    Point3D point2(1, 2, 2);
    Point3D point3(5, 6, 6);
    // Assert
    EXPECT_FALSE(point1 != point2);
}
TEST(TestPoint3DLib, get_distance_to) {
    // Arrange & Act
    Point3D point1(1, 2, 3);
    Point3D point2(5, 6, 7);
    // Assert
    EXPECT_EQ(point1.getDistanceTo(point2), 7);
}

*/