/*
** EPITECH PROJECT, 2022
** AForm.hpp
** File description:
** Header file for the Form Abstract class
*/

#pragma once

#ifndef AFORM_HPP_
    #define AFORM_HPP_

    #include "IForm.hpp"

    namespace RayTracer::Forms {
        class AForm : public IForm {
            public:
                virtual ~AForm() = default;

                std::string getName() const override final {
                    return _name;
                }

                RayTracer::Math::Color getColor() const override final {
                    return _color;
                }

                void setColor(const RayTracer::Math::Color &color) override final {
                    _color = color;
                }

                void setMaterial(const MaterialPtr &material) override final {
                    _material = material;
                }

                virtual double getRadius() const = 0;
                virtual RayTracer::Math::Point3D getCenter() const = 0;

                virtual void setRadius(double radius) = 0;
                virtual void setCenter(const RayTracer::Math::Point3D &center) = 0;

                virtual void setCenter0(const RayTracer::Math::Point3D &center0) = 0;
                virtual void setCenter1(const RayTracer::Math::Point3D &center1) = 0;

                virtual void setTime0(double time0) = 0;
                virtual void setTime1(double time1) = 0;

                virtual bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const = 0;

            protected:
                std::string _name;

                RayTracer::Math::Color _color;

                MaterialPtr _material;
        };
    }

#endif /* !AFORM_HPP_ */
