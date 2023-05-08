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

                std::tuple<short int, short int, short int> getColor() const override final {
                    return _color;
                }

                void setColor(const std::tuple<short int, short int, short int> &color) override final {
                    _color = color;
                }

                void setMaterial(const MaterialPtr &material) override final {
                    _material = material;
                }

                virtual double getRadius() const = 0;
                virtual RayTracer::Math::Point3D getCenter() const = 0;

                virtual void setRadius(double radius) = 0;
                virtual void setCenter(const RayTracer::Math::Point3D &center) = 0;

                virtual bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const = 0;

            protected:
                std::string _name;

                std::tuple<short int, short int, short int> _color;

                MaterialPtr _material;
        };
    }

#endif /* !AFORM_HPP_ */
