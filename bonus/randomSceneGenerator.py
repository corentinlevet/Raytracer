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
        "        x = 13;\n"
        "        y = 2;\n"
        "        z = 3;\n"
        "    };\n"
        "    direction = {\n"
        "        x = 0;\n"
        "        y = 0;\n"
        "        z = 0;\n"
        "    };\n"
        "    background = {\n"
        "        r = 0.7;\n"
        "        g = 0.8;\n"
        "        b = 1.0;\n"
        "    };\n"
        "    fieldOfView = 20.0;\n"
        "    aperture = 0.1;\n"
        "};\n"
    )

def main():
    file = open("scenes/randomScene.cfg", "w")
    writeCamera(file)
    file.write(
        "\n"
        "primitives:\n"
        "{\n"
        "    spheres = (\n"
        "        {\n"
        "            name = \"Sphere\";\n"
        "            x = 0.0;\n"
        "            y = -1000.0;\n"
        "            z = 0.0;\n"
        "            radius = 1000.0;\n"
        "            color = {\n"
        "                r = 0.0;\n"
        "                g = 0.0;\n"
        "                b = 0.0;\n"
        "            };\n"
        "            material = {\n"
        "                type = \"Material\";\n"
        "                name = \"Lambertian\";\n"
        "                albedo = {\n"
        "                    r = 0.5;\n"
        "                    g = 0.5;\n"
        "                    b = 0.5;\n"
        "                };\n"
        "                texture = {\n"
        "                    name = \"Checker\";\n"
        "                    properties = {\n"
        "                        color1 = {\n"
        "                            r = 0.0;\n"
        "                            g = 0.0;\n"
        "                            b = 0.0;\n"
        "                        };\n"
        "                        color2 = {\n"
        "                            r = 1.0;\n"
        "                            g = 1.0;\n"
        "                            b = 1.0;\n"
        "                        };\n"
        "                    };\n"
        "                };\n"
        "            };\n"
        "        },\n"
    )

    for a in range(-11, 12, 1):
        for b in range(-11, 12, 1):
            chooseMat = random.uniform(0, 1)
            center = (a + 0.9 * random.uniform(0, 1), 0.2, b + 0.9 * random.uniform(0, 1))

            if (center[0] - 4) * (center[0] - 4) + (center[1] - 0.2) * (center[1] - 0.2) + (center[2] - 0) * (center[2] - 0) > 0.9 * 0.9:
                if chooseMat < 0.8:
                    file.write(
                        "        {\n"
                        "            name = \"Sphere\";\n"
                        "            x = " + "{:.1f}".format(center[0]) + ";\n"
                        "            y = " + "{:.1f}".format(center[1]) + ";\n"
                        "            z = " + "{:.1f}".format(center[2]) + ";\n"
                        "            radius = 0.2;\n"
                        "            color = {\n"
                        "                r = 0.0;\n"
                        "                g = 0.0;\n"
                        "                b = 0.0;\n"
                        "            };\n"
                        "            material = {\n"
                        "                type = \"Material\";\n"
                        "                name = \"Lambertian\";\n"
                        "                albedo = {\n"
                        "                    r = " + "{:.1f}".format(random.uniform(0, 1)) + ";\n"
                        "                    g = " + "{:.1f}".format(random.uniform(0, 1)) + ";\n"
                        "                    b = " + "{:.1f}".format(random.uniform(0, 1)) + ";\n"
                        "                };\n"
                        "            };\n"
                        "        },\n"
                    )
                elif chooseMat < 0.95:
                    file.write(
                        "        {\n"
                        "            name = \"Sphere\";\n"
                        "            x = " + "{:.1f}".format(center[0]) + ";\n"
                        "            y = " + "{:.1f}".format(center[1]) + ";\n"
                        "            z = " + "{:.1f}".format(center[2]) + ";\n"
                        "            radius = 0.2;\n"
                        "            color = {\n"
                        "                r = 0.0;\n"
                        "                g = 0.0;\n"
                        "                b = 0.0;\n"
                        "            };\n"
                        "            material = {\n"
                        "                type = \"Material\";\n"
                        "                name = \"Metal\";\n"
                        "                albedo = {\n"
                        "                    r = " + "{:.1f}".format(random.uniform(0.5, 1)) + ";\n"
                        "                    g = " + "{:.1f}".format(random.uniform(0.5, 1)) + ";\n"
                        "                    b = " + "{:.1f}".format(random.uniform(0.5, 1)) + ";\n"
                        "                };\n"
                        "                fuzziness = " + "{:.1f}".format(random.uniform(0, 0.5)) + ";\n"
                        "            };\n"
                        "        },\n"
                    )
                else:
                    file.write(
                        "        {\n"
                        "            name = \"Sphere\";\n"
                        "            x = " + "{:.1f}".format(center[0]) + ";\n"
                        "            y = " + "{:.1f}".format(center[1]) + ";\n"
                        "            z = " + "{:.1f}".format(center[2]) + ";\n"
                        "            radius = 0.2;\n"
                        "            color = {\n"
                        "                r = 0.0;\n"
                        "                g = 0.0;\n"
                        "                b = 0.0;\n"
                        "            };\n"
                        "            material = {\n"
                        "                type = \"Material\";\n"
                        "                name = \"Dielectric\";\n"
                        "                refractionIndex = 1.5;\n"
                        "            };\n"
                        "        },\n"
                    )

    file.write(
        "        {\n"
        "            name = \"Sphere\";\n"
        "            x = 0.0;\n"
        "            y = 1.0;\n"
        "            z = 0.0;\n"
        "            radius = 1.0;\n"
        "            color = {\n"
        "                r = 0.0;\n"
        "                g = 0.0;\n"
        "                b = 0.0;\n"
        "            };\n"
        "            material = {\n"
        "                type = \"Material\";\n"
        "                name = \"Dielectric\";\n"
        "                refractionIndex = 1.5;\n"
        "            };\n"
        "        },\n"
        "        {\n"
        "            name = \"Sphere\";\n"
        "            x = -4.0;\n"
        "            y = 1.0;\n"
        "            z = 0.0;\n"
        "            radius = 1.0;\n"
        "            color = {\n"
        "                r = 0.0;\n"
        "                g = 0.0;\n"
        "                b = 0.0;\n"
        "            };\n"
        "            material = {\n"
        "                type = \"Material\";\n"
        "                name = \"Lambertian\";\n"
        "                albedo = {\n"
        "                    r = " + "{:.1f}".format(random.uniform(0, 1)) + ";\n"
        "                    g = " + "{:.1f}".format(random.uniform(0, 1)) + ";\n"
        "                    b = " + "{:.1f}".format(random.uniform(0, 1)) + ";\n"
        "                };\n"
        "            };\n"
        "        },\n"
        "        {\n"
        "            name = \"Sphere\";\n"
        "            x = 4.0;\n"
        "            y = 1.0;\n"
        "            z = 0.0;\n"
        "            radius = 1.0;\n"
        "            color = {\n"
        "                r = 0.0;\n"
        "                g = 0.0;\n"
        "                b = 0.0;\n"
        "            };\n"
        "            material = {\n"
        "                type = \"Material\";\n"
        "                name = \"Metal\";\n"
        "                albedo = {\n"
        "                    r = 0.7;\n"
        "                    g = 0.6;\n"
        "                    b = 0.5;\n"
        "                };\n"
        "                fuzziness = 0.0;\n"
        "            };\n"
        "        },\n"
    )

    file.write(
        "    );\n"
        "}\n"
    )

    file.close()

if __name__ == "__main__":
    main()