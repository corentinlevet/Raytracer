/*
** EPITECH PROJECT, 2022
** HitRecord.hpp
** File description:
** Header file for the HitRecord class
*/

#pragma once

#ifndef HITRECORD_HPP_
    #define HITRECORD_HPP_

    #include "IMaterial.hpp"

    #include "Point3D.hpp"

    namespace RayTracer {
        class Ray;
    }

    namespace RayTracer::Forms {
        class HitRecord {
            public:
                /* Constructors and destructors */

                /**
                 * @brief Constructs a new HitRecord object by giving the distance
                 *     (Default constructor)
                 * @param t The distance between the origin of the Ray and the hit point
                 * @param point The hit point
                 * @param normal The normal vector of the hit point
                **/
                HitRecord(double t = 0.0, const RayTracer::Math::Point3D &point = RayTracer::Math::Point3D(), const RayTracer::Math::Vector3D &normal = RayTracer::Math::Vector3D());

                /**
                 * @brief Destroys the HitRecord object
                 *
                 * @note This destructor is default
                **/
                ~HitRecord() = default;

                /* Getters and setters */

                bool isFrontFace() const {
                    return _frontFace;
                }

                double getT() const {
                    return _t;
                }

                std::shared_ptr<RayTracer::Materials::IMaterial> getMaterial() const {
                    return _material;
                }

                const RayTracer::Math::Point3D &getPoint() const {
                    return _point;
                }

                const RayTracer::Math::Vector3D &getNormal() const {
                    return _normal;
                }

                void setFrontFace(bool frontFace) {
                    _frontFace = frontFace;
                }

                void setT(double t) {
                    _t = t;
                }

                void setMaterial(const std::shared_ptr<RayTracer::Materials::IMaterial> &material) {
                    _material = material;
                }

                void setPoint(const RayTracer::Math::Point3D &point) {
                    _point = point;
                }

                void setNormal(const RayTracer::Math::Vector3D &normal) {
                    _normal = normal;
                }

                /* Methods */

                void setFaceNormal(const RayTracer::Ray &ray, const RayTracer::Math::Vector3D &outwardNormal);

            private:
                bool _frontFace;

                double _t;

                std::shared_ptr<RayTracer::Materials::IMaterial> _material;

                RayTracer::Math::Point3D _point;
                RayTracer::Math::Vector3D _normal;
        };
    }

#endif /* !HITRECORD_HPP_ */
