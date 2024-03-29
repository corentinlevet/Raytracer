import random, math

def writeCamera(file):
    file.write(
        "camera:\n"
        "{\n"
        "    aspectRatio = {\n"
        "        width = 16.0;\n"
        "        height = 9.0;\n"
        "    };\n"
        "    resolution = {\n"
        "        width = 400;\n"
        "        height = 400;\n"
        "    };\n"
        "    position = {\n"
        "        x = 478;\n"
        "        y = 278;\n"
        "        z = -600;\n"
        "    };\n"
        "    direction = {\n"
        "        x = 278;\n"
        "        y = 278;\n"
        "        z = 0;\n"
        "    };\n"
        "    background = {\n"
        "        r = 0.0;\n"
        "        g = 0.0;\n"
        "        b = 0.0;\n"
        "    };\n"
        "    fieldOfView = 40.0;\n"
        "    aperture = 0.0;\n"
        "    samplesPerPixel = 1024;\n"
        "    upscale = 1;\n"
        "};\n"
    )

def writeGround(file):
    file.write(
        "\n"
        "primitives:\n"
        "{\n"
        "    bvh = (\n"
        "        {\n"
        "            primitives = {\n"
        "                boxes = (\n"
    )

    for i in range(0, 20):
        for j in range(0,20):
            w = 100.0
            x0 = -1000.0 + i * w
            z0 = -1000.0 + j * w
            y0 = 0.0
            x1 = x0 + w
            y1 = 100.0 * (random.uniform(0, 1) + 0.01)
            z1 = z0 + w

            file.write(
                "                    {\n"
                "                        name = \"Box\";\n"
                "                        point0 = {\n"
                "                            x = " + "{:.1f}".format(x0) + ";\n"
                "                            y = " + "{:.1f}".format(y0) + ";\n"
                "                            z = " + "{:.1f}".format(z0) + ";\n"
                "                        };\n"
                "                        point1 = {\n"
                "                            x = " + "{:.1f}".format(x1) + ";\n"
                "                            y = " + "{:.1f}".format(y1) + ";\n"
                "                            z = " + "{:.1f}".format(z1) + ";\n"
                "                        };\n"
                "                        material = {\n"
                "                            type = \"Material\";\n"
                "                            name = \"Lambertian\";\n"
                "                            texture = {\n"
                "                                name = \"SolidColor\";\n"
                "                                properties = {\n"
                "                                    color = {\n"
                "                                        r = 0.48;\n"
                "                                        g = 0.83;\n"
                "                                        b = 0.53;\n"
                "                                    };\n"
                "                                };\n"
                "                            };\n"
                "                        };\n"
                "                    },\n"
            )

    file.write(
        "                );\n"
        "            };\n"
        "        },\n"
        "        {\n"
        "            primitives = {\n"
        "                spheres = (\n"
    )

    for _ in range(0, 1000):
        center = (random.uniform(0, 1) * 165.0, random.uniform(0, 1) * 165.0, random.uniform(0, 1) * 165.0)

        file.write(
            "                    {\n"
            "                        name = \"Sphere\";\n"
            "                        x = " + "{:.1f}".format(center[0]) + ";\n"
            "                        y = " + "{:.1f}".format(center[1]) + ";\n"
            "                        z = " + "{:.1f}".format(center[2]) + ";\n"
            "                        radius = 10.0;\n"
            "                        color = {\n"
            "                            r = 0;\n"
            "                            g = 0;\n"
            "                            b = 0;\n"
            "                        };\n"
            "                        material = {\n"
            "                            type = \"Material\";\n"
            "                            name = \"Lambertian\";\n"
            "                            texture = {\n"
            "                                name = \"SolidColor\";\n"
            "                                properties = {\n"
            "                                    color = {\n"
            "                                        r = 0.7;\n"
            "                                        g = 0.7;\n"
            "                                        b = 0.7;\n"
            "                                    };\n"
            "                                };\n"
            "                            };\n"
            "                        };\n"
            "                    },\n"
        )

    file.write(
        "                );\n"
        "            };\n"
        "            transformations = (\n"
        "                {\n"
        "                    type = \"RotateY\";\n"
        "                    properties = {\n"
        "                        angle = 15.0;\n"
        "                    };\n"
        "                },\n"
        "                {\n"
        "                    type = \"Translate\";\n"
        "                    properties = {\n"
        "                        x = -100.0;\n"
        "                        y = 270.0;\n"
        "                        z = 395.0;\n"
        "                    };\n"
        "                },\n"
        "            );\n"
        "        },\n"
        "    );\n"
    )

def writeLight(file):
    file.write(
        "\n"
        "    rectangles = (\n"
        "        {\n"
        "            name = \"RectangleXZ\";\n"
        "            x0 = 123.0;\n"
        "            x1 = 423.0;\n"
        "            z0 = 147.0;\n"
        "            z1 = 412.0;\n"
        "            k = 554.0;\n"
        "            color = {\n"
        "                r = 0;\n"
        "                g = 0;\n"
        "                b = 0;\n"
        "            };\n"
        "            material = {\n"
        "                type = \"Light\";\n"
        "                name = \"Diffuse\";\n"
        "                texture = {\n"
        "                    name = \"SolidColor\";\n"
        "                    properties = {\n"
        "                        color = {\n"
        "                            r = 7.0;\n"
        "                            g = 7.0;\n"
        "                            b = 7.0;\n"
        "                        };\n"
        "                    };\n"
        "                };\n"
        "            };\n"
        "        },\n"
        "    );\n"
    )

def writeSpheres(file):
    file.write(
        "\n"
        "    spheres = (\n"
        "        {\n"
        "            name = \"MovingSphere\";\n"
        "            x0 = 400.0;\n"
        "            y0 = 400.0;\n"
        "            z0 = 200.0;\n"
        "            x1 = 430.0;\n"
        "            y1 = 400.0;\n"
        "            z1 = 200.0;\n"
        "            radius = 50.0;\n"
        "            color = {\n"
        "                r = 0;\n"
        "                g = 0;\n"
        "                b = 0;\n"
        "            };\n"
        "            material = {\n"
        "                type = \"Material\";\n"
        "                name = \"Lambertian\";\n"
        "                texture = {\n"
        "                    name = \"SolidColor\";\n"
        "                    properties = {\n"
        "                        color = {\n"
        "                            r = 0.7;\n"
        "                            g = 0.3;\n"
        "                            b = 0.1;\n"
        "                        };\n"
        "                    };\n"
        "                };\n"
        "            };\n"
        "        },\n"
        "        {\n"
        "            name = \"Sphere\";\n"
        "            x = 260.0;\n"
        "            y = 150.0;\n"
        "            z = 45.0;\n"
        "            radius = 50.0;\n"
        "            color = {\n"
        "                r = 0;\n"
        "                g = 0;\n"
        "                b = 0;\n"
        "            };\n"
        "            material = {\n"
        "                type = \"Material\";\n"
        "                name = \"Dielectric\";\n"
        "                refractionIndex = 1.5;\n"
        "            };\n"
        "        },\n"
        "        {\n"
        "            name = \"Sphere\";\n"
        "            x = 0.0;\n"
        "            y = 150.0;\n"
        "            z = 145.0;\n"
        "            radius = 50.0;\n"
        "            color = {\n"
        "                r = 0;\n"
        "                g = 0;\n"
        "                b = 0;\n"
        "            };\n"
        "            material = {\n"
        "                type = \"Material\";\n"
        "                name = \"Metal\";\n"
        "                albedo = {\n"
        "                    r = 0.8;\n"
        "                    g = 0.8;\n"
        "                    b = 0.9;\n"
        "                };\n"
        "                fuzziness = 1.0;\n"
        "            };\n"
        "        },\n"
        "        {\n"
        "            name = \"Sphere\";\n"
        "            x = 360.0;\n"
        "            y = 150.0;\n"
        "            z = 145.0;\n"
        "            radius = 70.0;\n"
        "            color = {\n"
        "                r = 0;\n"
        "                g = 0;\n"
        "                b = 0;\n"
        "            };\n"
        "            material = {\n"
        "                type = \"Material\";\n"
        "                name = \"Dielectric\";\n"
        "                refractionIndex = 1.5;\n"
        "            };\n"
        "        },\n"
        "        {\n"
        "            name = \"Sphere\";\n"
        "            x = 360.0;\n"
        "            y = 150.0;\n"
        "            z = 145.0;\n"
        "            radius = 70.0;\n"
        "            color = {\n"
        "                r = 0;\n"
        "                g = 0;\n"
        "                b = 0;\n"
        "            };\n"
        "            material = {\n"
        "                type = \"Material\";\n"
        "                name = \"Dielectric\";\n"
        "                refractionIndex = 1.5;\n"
        "            };\n"
        "            transformations = (\n"
        "                {\n"
        "                    type = \"ConstantMedium\";\n"
        "                    properties = {\n"
        "                        density = 0.2;\n"
        "                        color = {\n"
        "                            r = 0.2;\n"
        "                            g = 0.4;\n"
        "                            b = 0.9;\n"
        "                        };\n"
        "                    };\n"
        "                },\n"
        "            );\n"
        "        },\n"
        "        {\n"
        "            name = \"Sphere\";\n"
        "            x = 0.0;\n"
        "            y = 0.0;\n"
        "            z = 0.0;\n"
        "            radius = 5000.0;\n"
        "            color = {\n"
        "                r = 0;\n"
        "                g = 0;\n"
        "                b = 0;\n"
        "            };\n"
        "            material = {\n"
        "                type = \"Material\";\n"
        "                name = \"Dielectric\";\n"
        "                refractionIndex = 1.5;\n"
        "            };\n"
        "            transformations = (\n"
        "                {\n"
        "                    type = \"ConstantMedium\";\n"
        "                    properties = {\n"
        "                        density = 0.0001;\n"
        "                        color = {\n"
        "                            r = 1.0;\n"
        "                            g = 1.0;\n"
        "                            b = 1.0;\n"
        "                        };\n"
        "                    };\n"
        "                },\n"
        "            );\n"
        "        },\n"
        "        {\n"
        "            name = \"Sphere\";\n"
        "            x = 400.0;\n"
        "            y = 200.0;\n"
        "            z = 400.0;\n"
        "            radius = 100.0;\n"
        "            color = {\n"
        "                r = 0;\n"
        "                g = 0;\n"
        "                b = 0;\n"
        "            };\n"
        "            material = {\n"
        "                type = \"Material\";\n"
        "                name = \"Lambertian\";\n"
        "                texture = {\n"
        "                    name = \"Image\";\n"
        "                    properties = {\n"
        "                        path = \"assets/earthmap.jpg\";\n"
        "                    };\n"
        "                };\n"
        "            };\n"
        "        },\n"
        "        {\n"
        "            name = \"Sphere\";\n"
        "            x = 220.0;\n"
        "            y = 280.0;\n"
        "            z = 300.0;\n"
        "            radius = 80.0;\n"
        "            color = {\n"
        "                r = 0;\n"
        "                g = 0;\n"
        "                b = 0;\n"
        "            };\n"
        "            material = {\n"
        "                type = \"Material\";\n"
        "                name = \"Lambertian\";\n"
        "                albedo = {\n"
        "                    r = 1.0;\n"
        "                    g = 1.0;\n"
        "                    b = 1.0;\n"
        "                };\n"
        "                texture = {\n"
        "                    name = \"Perlin\";\n"
        "                    properties = {\n"
        "                        scale = 0.1;\n"
        "                    };\n"
        "                };\n"
        "            };\n"
        "        },\n"
        "    );\n"
    )

def main():
    file = open("scenes/finalScene.cfg", "w")
    writeCamera(file)
    writeGround(file)
    writeLight(file)
    writeSpheres(file)

    file.write(
        "}\n"
    )

    file.close()

if __name__ == "__main__":
    main()
