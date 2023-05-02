/*
** EPITECH PROJECT, 2022
** DLLoader.hpp
** File description:
** Header file for the DLLoader class
*/

#pragma once

#ifndef DLLOADER_HPP_
    #define DLLOADER_HPP_

    #include "Error.hpp"

    #include <dlfcn.h>
    #include <string>
    #include <memory>

    class DLLoader {
        public:
            DLLoader() = default;
            ~DLLoader() = default;

            /**
             * @brief Loads a dynamic library
             *
             * @tparam T The type of the library
             * @param path The path to the library
             * @return std::unique_ptr<T> A pointer to the library
            **/
            template<typename T>
            static std::unique_ptr<T> loadLibrary(const std::string &path) {
                void *handle = dlopen(path.c_str(), RTLD_LAZY);

                if (!handle)
                    throw DLLoader::hardError("loadLibrary", "Failed to load library: " + std::string(dlerror()));

                std::unique_ptr<T> (*entryPoint)() = reinterpret_cast<std::unique_ptr<T>(*)()>(dlsym(handle, "entryPoint"));

                if (!entryPoint)
                    throw DLLoader::hardError("loadLibrary", "Failed to load entry point: " + std::string(dlerror()));

                return entryPoint();
            }

            /**
             * @brief Closes a dynamic library
             *
             * @tparam T The type of the library
             * @param library The library to close
             * @return void
            **/
            template<typename T>
            static void closeLibrary(std::unique_ptr<T> &library) {
                if (dlclose(library.get()))
                    throw DLLoader::hardError("closeLibrary", "Failed to close library: " + std::string(dlerror()));
            }

            class softError : public RayTracer::Error {
                public:
                    softError(const std::string &where, const std::string &what) : Error("DLLoader::" + where, what) {}
                    ~softError() = default;
            };

            class hardError : public RayTracer::Error {
                public:
                    hardError(const std::string &where, const std::string &what) : Error("DLLoader::" + where, what) {}
                    ~hardError() = default;
            };
    };

#endif /* !DLLOADER_HPP_ */
