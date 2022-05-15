#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <bits/stdc++.h>
#include <unistd.h>

#include "camera.h"
#include "shader.h"


#define PREDEFINED_X 5.0f
#define PREDEFINED_Y 5.0f
#define PREDEFINED_Z 5.0f

#define CAMERA_TRANSLATION_INCREMENT 0.05f
#define OBJECT_TRANSLATION_INCREMENT 0.05f

glm::vec3 initcamerapos = glm::vec3(0.0f, 0.0f, 5.0f);
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

glm::vec3 objectcentre = glm::vec3(0.0f,0.0f,0.0f);

glm::vec3 predefinedpos1 = glm::vec3(5.0f, 5.0f, 5.0f);
glm::vec3 predefinedpos2 = glm::vec3(-5.0f, 5.0f, 5.0f);

float theta = 0.0f;
float increment_theta = 0.01f;
float anglerotation = 0.0f;
float initzpos = camera.Position.z;
bool pressedt = false;
bool pressedr = false;
bool pressed1 = false;
bool pressed2 = false;
bool pressed12 = false;
glm::mat4 transform = glm::mat4(1.0f);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
        pressedt = !pressedt;

    if (key == GLFW_KEY_R && action == GLFW_PRESS)
        pressedr = !pressedr;
}

void processInput(GLFWwindow *window)
{
    glm::vec3 forback = glm::vec3(0.0f, 0.0f, CAMERA_TRANSLATION_INCREMENT);
    glm::vec3 leftright = glm::vec3(CAMERA_TRANSLATION_INCREMENT, 0.0f, 0.0f);
    glm::vec3 updown = glm::vec3(0.0f, CAMERA_TRANSLATION_INCREMENT, 0.0f);
    float radius = 5.0f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {   
        //std::cout << camera.Front.x << " " << camera.Front.y << " " << camera.Front.z << " " << objectcentre.x << " " << objectcentre.y << " " << objectcentre.z << "\n";
        if(camera.Front != objectcentre)
        {
            camera.Front = objectcentre;
        }
        //std::cout << camera.Front.x << " " << camera.Front.y << " " << camera.Front.z << " " << objectcentre.x << " " << objectcentre.y << " " << objectcentre.z << "\n";
        camera.Position -= forback;
    }

    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        if(camera.Front != objectcentre)
        {
            camera.Front = objectcentre;
        }
        camera.Position += forback;
    }

    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        if(camera.Front != objectcentre)
        {
            camera.Front = objectcentre;
        }
        camera.Position -= leftright;
    }

    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        if(camera.Front != objectcentre)
        {
            camera.Front = objectcentre;
        }
        camera.Position += leftright;
    }

    else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        if(camera.Front != objectcentre)
        {
            camera.Front = objectcentre;
        }
        camera.Position += updown;
    }

    else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        if(camera.Front != objectcentre)
        {
            camera.Front = objectcentre;
        }
        camera.Position -= updown;
    }

    else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        transform = glm::translate(transform, glm::vec3(0.0f, OBJECT_TRANSLATION_INCREMENT, 0.0f));
        objectcentre.y += OBJECT_TRANSLATION_INCREMENT;
    }

    else if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
    {
        transform = glm::translate(transform, glm::vec3(0.0f, -OBJECT_TRANSLATION_INCREMENT, 0.0f));
        objectcentre.y -= OBJECT_TRANSLATION_INCREMENT;
    }

    else if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    {
        transform = glm::translate(transform, glm::vec3(OBJECT_TRANSLATION_INCREMENT, 0.0f, 0.0f));
        objectcentre.x += OBJECT_TRANSLATION_INCREMENT;
    }

    else if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
        transform = glm::translate(transform, glm::vec3(-OBJECT_TRANSLATION_INCREMENT, 0.0f, 0.0f));
        objectcentre.x -= OBJECT_TRANSLATION_INCREMENT;
    }

    else if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        transform = glm::translate(transform, glm::vec3(0.00f, 0.0f, OBJECT_TRANSLATION_INCREMENT));
        objectcentre.z += OBJECT_TRANSLATION_INCREMENT;
    }

    else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {

        transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, -OBJECT_TRANSLATION_INCREMENT));
        objectcentre.z -= OBJECT_TRANSLATION_INCREMENT;
    }

    else if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        camera.Position = predefinedpos1;
    }

    else if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        camera.Position = predefinedpos2;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina
    // displays.
    glViewport(0, 0, width, height);
}
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

// camera

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        std::cout << "Please Enter N\n";
        return 0;
    }

    int n = atoi(argv[1]);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow *window =
        glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    Shader ourShader("vertex.shader", "fragment.shader");
    float side = (float)n;
    std::vector<float> SeqVert;

    for (int i = 0; i < n; i++)
    {
        SeqVert.push_back((float)glm::cos(glm::radians((double)(2 * (i + 1) * 180 / side))));
        SeqVert.push_back((float)glm::sin(glm::radians((double)(2 * (i + 1) * 180 / side))));
        SeqVert.push_back(0.5f);
    }

    for (int i = 0; i < n; i++)
    {
        SeqVert.push_back((float)glm::cos(glm::radians((double)(2 * (i + 1) * 180 / side))));
        SeqVert.push_back((float)glm::sin(glm::radians((double)(2 * (i + 1) * 180 / side))));
        SeqVert.push_back(-0.5f);
    }

    std::vector<float> VERT;

    for (int i = 0; i < n - 2; i++)
    {
        VERT.push_back(1.0f);
        VERT.push_back(0.0f);
        VERT.push_back(0.5f);

        VERT.push_back((float)glm::cos(glm::radians((double)(2 * (i + 1) * 180 / side))));
        VERT.push_back((float)glm::sin(glm::radians((double)(2 * (i + 1) * 180 / side))));
        VERT.push_back(0.5f);

        VERT.push_back((float)glm::cos(glm::radians((double)(2 * (i + 2) * 180 / side))));
        VERT.push_back((float)glm::sin(glm::radians((double)(2 * (i + 2) * 180 / side))));
        VERT.push_back(0.5f);
    }

    for (int i = 0; i < n; i++)
    {
        int vx1 = i;
        int vx2 = i + 1;
        int vx3 = vx2 + n;
        int vx4 = vx1 + n;

        if (vx1 == n - 1)
        {
            vx2 = 0;
            vx3 = n;
            vx4 = 2 * n - 1;
        }

        VERT.push_back(SeqVert[3 * vx1]);
        VERT.push_back(SeqVert[3 * vx1 + 1]);
        VERT.push_back(SeqVert[3 * vx1 + 2]);

        VERT.push_back(SeqVert[3 * vx2]);
        VERT.push_back(SeqVert[3 * vx2 + 1]);
        VERT.push_back(SeqVert[3 * vx2 + 2]);

        VERT.push_back(SeqVert[3 * vx3]);
        VERT.push_back(SeqVert[3 * vx3 + 1]);
        VERT.push_back(SeqVert[3 * vx3 + 2]);

        VERT.push_back(SeqVert[3 * vx1]);
        VERT.push_back(SeqVert[3 * vx1 + 1]);
        VERT.push_back(SeqVert[3 * vx1 + 2]);

        VERT.push_back(SeqVert[3 * vx3]);
        VERT.push_back(SeqVert[3 * vx3 + 1]);
        VERT.push_back(SeqVert[3 * vx3 + 2]);

        VERT.push_back(SeqVert[3 * vx4]);
        VERT.push_back(SeqVert[3 * vx4 + 1]);
        VERT.push_back(SeqVert[3 * vx4 + 2]);
    }

    for (int i = 0; i < n - 2; i++)
    {
        VERT.push_back(1.0f);
        VERT.push_back(0.0f);
        VERT.push_back(-0.5f);

        VERT.push_back((float)glm::cos(glm::radians((double)(2 * (i + 1) * 180 / side))));
        VERT.push_back((float)glm::sin(glm::radians((double)(2 * (i + 1) * 180 / side))));
        VERT.push_back(-0.5f);

        VERT.push_back((float)glm::cos(glm::radians((double)(2 * (i + 2) * 180 / side))));
        VERT.push_back((float)glm::sin(glm::radians((double)(2 * (i + 2) * 180 / side))));
        VERT.push_back(-0.5f);
    }

    int npoints = 9 * (2 * (n - 2) + 2 * n);
    float finalvert[npoints];
    std::copy(VERT.begin(), VERT.end(), finalvert);

    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(finalvert), finalvert, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwSetKeyCallback(window, key_callback);
    // glEnable(GL_LINE_SMOOTH);
    // glHint(GL_LINE_SMOOTH_HINT,  GL_NICEST);

    srand(time(0));
    glm::vec4 colorarr[n + 2];
    for (int i = 0; i < n + 2; i++)
    {
        colorarr[i] = glm::vec4((rand() % 255) / 255.0f, (rand() % 255) / 255.0f, (rand() % 255) / 255.0f, 1.0f);
    }

    while (!glfwWindowShouldClose(window))
    {

        if (pressedt)
        {
            pressedt = false;
            float PI = glm::pi<float>();
            if(camera.Front != objectcentre)
            {
                camera.Front = objectcentre;
            }
            theta = atan(camera.Position.x/camera.Position.z);

            if(camera.Position.x > 0 && camera.Position.z < 0)
                theta += PI;
            
            if(camera.Position.x < 0 && camera.Position.z < 0)
                theta += PI;

            while (1)
            {

                camera.Position.x = glm::abs(initcamerapos.z) * sin(theta);
                camera.Position.z = glm::abs(initcamerapos.z) * cos(theta);
                // std::cout << camera.Position.x << " ";
                // std::cout << camera.Position.z << "\n";
                glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // make transformations
                //transform = glm::mat4(1.0f); // identity matrix

                ourShader.use();
                ourShader.setMat4("transform", transform);

                // view matrix
                glm::mat4 view = camera.GetViewMatrix(glm::vec3(0.0f));
                ourShader.setMat4("view", view);

                // projection matrix
                glm::mat4 projection = glm::perspective(
                    glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
                    0.1f, 100.0f);
                ourShader.setMat4("projection", projection);

                glBindVertexArray(VAO);
                glm::vec4 color;

                color = colorarr[n + 1];
                ourShader.setVec4("ourCol", color);
                glDrawArrays(GL_TRIANGLES, 3 * ((n - 2) + 2 * n), 3 * (n - 2));

                float r = 0.1f;
                for (int i = 1; i <= n; i++)
                {
                    color = colorarr[i];
                    ourShader.setVec4("ourCol", color);
                    glDrawArrays(GL_TRIANGLES, 3 * ((n - 2) + 2 * (i - 1)), 6);
                }

                color = colorarr[0];
                ourShader.setVec4("ourCol", color);
                glDrawArrays(GL_TRIANGLES, 0, 3 * (n - 2));

                glfwSwapBuffers(window);
                glfwPollEvents();
                theta += increment_theta;
                if (pressedt)
                    break;
                // std::cout << theta << "\n";
            }
            pressedt = false;
        }

        if (pressedr)
        {
            pressedr = false;
            float PI = glm::pi<float>();
            float inc = 1.0f;
            // identity matrix
            while (1)
            {
                glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // make transformations

                transform = glm::rotate(transform, glm::radians(inc),
                                        glm::vec3(0.0f, 0.0f, 1.0f));

                ourShader.use();
                ourShader.setMat4("transform", transform);

                // view matrix
                glm::mat4 view = camera.GetViewMatrix(glm::vec3(0.0f));
                ourShader.setMat4("view", view);

                // projection matrix
                glm::mat4 projection = glm::perspective(
                    glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
                    0.1f, 100.0f);
                ourShader.setMat4("projection", projection);

                glBindVertexArray(VAO);
                glm::vec4 color;

                color = colorarr[n + 1];
                ourShader.setVec4("ourCol", color);
                glDrawArrays(GL_TRIANGLES, 3 * ((n - 2) + 2 * n), 3 * (n - 2));

                float r = 0.1f;
                for (int i = 1; i <= n; i++)
                {
                    color = colorarr[i];
                    ourShader.setVec4("ourCol", color);
                    glDrawArrays(GL_TRIANGLES, 3 * ((n - 2) + 2 * (i - 1)), 6);
                }

                color = colorarr[0];
                ourShader.setVec4("ourCol", color);
                glDrawArrays(GL_TRIANGLES, 0, 3 * (n - 2));

                glfwSwapBuffers(window);
                glfwPollEvents();
                if (pressedr)
                    break;
            }
            pressedr = false;
        }
        // input
        processInput(window);
        // render
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //transform = glm::mat4(1.0f);
        // make transformations
        ourShader.use();
        ourShader.setMat4("transform", transform);

        // view matrix
        glm::mat4 view = camera.GetViewMatrix(glm::vec3(0.0f));
        ourShader.setMat4("view", view);

        // projection matrix
        glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT,
            0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        glBindVertexArray(VAO);
        glm::vec4 color;

        color = colorarr[n + 1];
        ourShader.setVec4("ourCol", color);
        glDrawArrays(GL_TRIANGLES, 3 * ((n - 2) + 2 * n), 3 * (n - 2));

        float r = 0.1f;
        for (int i = 1; i <= n; i++)
        {
            color = colorarr[i];
            ourShader.setVec4("ourCol", color);
            glDrawArrays(GL_TRIANGLES, 3 * ((n - 2) + 2 * (i - 1)), 6);
        }

        color = colorarr[0];
        ourShader.setVec4("ourCol", color);
        glDrawArrays(GL_TRIANGLES, 0, 3 * (n - 2));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// g++ finalmain.cpp glad.c -lglfw -lGL -lX11 -lXrandr -lXi -ldl -lpthread