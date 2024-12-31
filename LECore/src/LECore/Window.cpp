//
// Created by Jack Daniels on 06.12.2024.
// 
// Changed by Jack Daniels on 07.12.2024
// Changed by Ganza on 31.12.2024

#include "LECore/Window.h"
#include "LECore/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

namespace LamaEngine
{
    static bool s_GLFW_initialized = false;

    //code shader triengle
    GLfloat point[] = 
    {
     0.0f, 0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     -0.5f, -0.5f, 0.0f
    };

    GLfloat colors[] = 
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    const char* vertex_shader =
        "#version 460\n"
        "layout(location = 0) in vec3 vertex_position;"
        "layout(location = 1) in vec3 vertex_color;"
        "out vec3 color;"
        "void main() {"
        "   color = vertex_color;"
        "   gl_Position = vec4(vertex_position, 1.0);"
        "}";

    const char* fragment_shader =
        "#version 460\n"
        "in vec3 color;"
        "out vec4 frag_color;"
        "void main() {"
        "   frag_color = vec4(color, 1.0);"
        "}";

        GLuint shader_program;
        GLuint vao;
        
	Window::Window(std::string title, const unsigned int width, const unsigned int height)
        : m_data({ std::move(title), width, height })
	{
		int resultCode = init();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplOpenGL3_Init();
        ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
	}
	Window::~Window()
	{
		shotdown();
	}
	int Window::init()
	{
        LOG_INFO("Creating window {0} with size {1}x{2}", m_data.title, m_data.width, m_data.height);
        if (!s_GLFW_initialized)
        {
            /* Initialize the library */
            if (!glfwInit())
            {
                LOG_CRITICAL("Can't initialize GLFW!");
                return -1;
            }
            s_GLFW_initialized = true;
        }

        /* Create a windowed mode window and its OpenGL context */
        m_pWindow = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
        if (!m_pWindow)
        {
            LOG_CRITICAL("Can't create window!");
            glfwTerminate();
            return -2;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(m_pWindow);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_CRITICAL("Failed to init GLAD");
            return -3;
        }

        glfwSetWindowUserPointer(m_pWindow, &m_data);

        glfwSetWindowSizeCallback(m_pWindow,
            [](GLFWwindow* pWindow, int width, int height)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                data.width = width;
                data.height = height;

                EventWindowResize event(width, height);
                data.eventCallbackFn(event);
            }
        );

        glfwSetCursorPosCallback(m_pWindow,
            [](GLFWwindow* pWindow, double x, double y)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
                data.width = x;
                data.height = y;

                EventMouseMoved event(x, y);
                data.eventCallbackFn(event);
            }
        );

        glfwSetWindowCloseCallback(m_pWindow,
            [](GLFWwindow* pWindow)
            {
                WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

                EventWindowClose event;
                data.eventCallbackFn(event);
            }
        );

        glfwSetFramebufferSizeCallback(m_pWindow,
            [](GLFWwindow* pWindow, int width, int height)
            {   //set to drow triangle
                glViewport(0, 0, width, height);
            }
        );


        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertex_shader, nullptr);
        glCompileShader(vs);
        //create shader & compile
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragment_shader, nullptr);
        glCompileShader(fs);
        //link shaders vs&fs
        shader_program = glCreateProgram();
        glAttachShader(shader_program, vs);
        glAttachShader(shader_program, fs);
        glLinkProgram(shader_program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        //fill memory GPU triengle for Drow
        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
        //event data GPU moment
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        //by zero is meant local_pos = 0; in vertex_shader
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        
        //checking for shader compilation
        int success;
        char infoLog[512];
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vs, 512, NULL, infoLog);
            LOG_CRITICAL("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}", infoLog);
        }
        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fs, 512, NULL, infoLog);
            LOG_CRITICAL("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{}", infoLog);
        }

        return 0;
	}

	void Window::shotdown()
	{
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
	}

    void Window::on_update()
    {
        glClearColor(m_background_color[0], m_background_color[1], m_background_color[2], m_background_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);
        //drow triengle shader
        glUseProgram(shader_program);
        glBindVertexArray(vao);//vao = vertex array obj
        glDrawArrays(GL_TRIANGLES, 0, 3);

        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize.x = static_cast<float>(get_width());
        io.DisplaySize.y = static_cast<float>(get_height());

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Background Color Window");
        ImGui::ColorEdit4("Background Color", m_background_color);
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(m_pWindow);
        glfwPollEvents();
    }
}