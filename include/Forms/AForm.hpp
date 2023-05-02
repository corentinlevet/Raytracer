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

                std::string getType() const override final {
                    return _type;
                }

                virtual double getRadius() const = 0;
                virtual RayTracer::Math::Point3D getCenter() const = 0;

                virtual void setRadius(double radius) = 0;
                virtual void setCenter(const RayTracer::Math::Point3D &center) = 0;

                virtual bool hits(const RayTracer::Ray &ray) const = 0;

            protected:
                std::string _type;
        };
    }

#endif /* !AFORM_HPP_ */
