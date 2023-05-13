/*
** EPITECH PROJECT, 2022
** Box.hpp
** File description:
** Header file for the Box class
*/

#pragma once

#ifndef BOX_HPP_
    #define BOX_HPP_

    #include "FormList.hpp"

    namespace RayTracer::Forms {
        class Box : public AForm {
            public:
                Box(const RayTracer::Math::Point3D &p0 = RayTracer::Math::Point3D(0, 0, 0), const RayTracer::Math::Point3D &p1 = RayTracer::Math::Point3D(1, 1, 1), const MaterialPtr &material = nullptr);
                ~Box() = default;

                void initBox(const RayTracer::Math::Point3D &p0, const RayTracer::Math::Point3D &p1, const MaterialPtr &material) override;

                bool hits(const RayTracer::Ray &ray, double t_min, double t_max, HitRecord &hitRecord) const override;
                bool boundingBox(double time0, double time1, AxisAlignedBoundingBox &boundingBox) const override;

            private:
                RayTracer::Forms::FormList _sides;

                RayTracer::Math::Point3D _p0;
                RayTracer::Math::Point3D _p1;
        };
    }

    extern "C"
    {
        FormPtr entryPointForm();
    }

#endif /* !BOX_HPP_ */
