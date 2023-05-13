/*
** EPITECH PROJECT, 2022
** IForm.hpp
** File description:
** Header file for the Form Interface class
*/

#pragma once

#ifndef IFORM_HPP_
    #define IFORM_HPP_

    #include <memory>
    #include <string>

    #include "IMaterial.hpp"
    #include "Point3D.hpp"
    #include "Utils.hpp"

    namespace RayTracer {
        class Ray;
        namespace Forms {
            class AxisAlignedBoundingBox;
            class HitRecord;
        }
    }

    namespace RayTracer::Forms {
        class IForm {
            public:
                virtual ~IForm() = default;

                /**
                 * @brief Get the Type of the Form
                 *
                 * @return std::string The type of the Form
                **/
                virtual std::string getName() const = 0;

                /**
                 * @brief Get the Color of the Form
                 *
                 * @return RayTracer::Math::Color The color of the Form
                **/
                virtual RayTracer::Math::Color getColor() const = 0;

                /**
                 * @brief Set the Color of the Form
                 *
                 * @param color The new color of the Form
                **/
                virtual void setColor(const RayTracer::Math::Color &color) = 0;

                /**
                 * @brief Get the Material of the Form
                 *
                 * @return RayTracer::Materials::IMaterial& The material of the Form
                **/
                virtual void setMaterial(const MaterialPtr &material) = 0;

                virtual AxisAlignedBoundingBox getBoundingBox() const = 0;

                virtual std::shared_ptr<RayTracer::Forms::IForm> getLeft() const = 0;
                virtual std::shared_ptr<RayTracer::Forms::IForm> getRight() const = 0;

                virtual void setRadius(double radius) = 0;
                virtual void setCenter(const RayTracer::Math::Point3D &center) = 0;

                virtual void setCenter0(const RayTracer::Math::Point3D &center0) = 0;
                virtual void setCenter1(const RayTracer::Math::Point3D &center1) = 0;

                virtual void setTime0(double time0) = 0;
                virtual void setTime1(double time1) = 0;

                virtual void setBoundingBox(const AxisAlignedBoundingBox &boundingBox) = 0;

                virtual void setLeft(const std::shared_ptr<RayTracer::Forms::IForm> &left) = 0;
                virtual void setRight(const std::shared_ptr<RayTracer::Forms::IForm> &right) = 0;

                virtual void initRectangle(double x0, double x1, double y0, double y1, double z0, double z1, double k) = 0;
                virtual void initBox(const RayTracer::Math::Point3D &p0, const RayTracer::Math::Point3D &p1, const MaterialPtr &material) = 0;

                /**
                 * @brief Checks if the Ray hits the Form
                 *
                 * @param ray The Ray to check
                 * @return true If the Ray hits the Form
                 * @return false If the Ray doesn't hit the Form
                **/
                virtual bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const = 0;

                /**
                 * @brief Get the Bounding Box of the Form
                 *
                 * @param t0 The minimum time
                 * @param t1 The maximum time
                 * @param boundingBox The bounding box
                 * @return true If the Ray hits the Form
                 * @return false If the Ray doesn't hit the Form
                **/
                virtual bool boundingBox(double t0, double t1, AxisAlignedBoundingBox &boundingBox) const = 0;
        };
    }

    typedef std::shared_ptr<RayTracer::Forms::IForm> FormPtr;

#endif /* !IFORM_HPP_ */
