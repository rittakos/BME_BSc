#include <cstdio>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

//#define _CRT_NONSTDC_NO_WARNINGS_GLOBALS
//#pragma warning (disable : 4996)

class FilePtr 
{

public:

    explicit FilePtr(FILE* fp = nullptr) : fp_{ fp }
    {

    }

    explicit FilePtr(const std::string filename, const std::string mode) : filename_{filename}
    {
        //fopen_s(&fp_, filename.c_str(), mode.c_str());
        fp_ = fopen(filename.c_str(), mode.c_str());
        if (fp_ == nullptr)
            throw("nem jott letre file");
    }

    ~FilePtr() 
    {
        close_if_open();
    }

    FilePtr& operator=(FILE* fp) 
    {
        close_if_open();
        fp_ = fp;
        return *this;
    }

    operator FILE* () const 
    {
        return fp_;
    }

    /* nem másolható */
    FilePtr(FilePtr const&) = delete;
    FilePtr& operator=(FilePtr const&) = delete;

    FilePtr(FilePtr&& other)
    {
        filename_ = other.filename_;
        fp_ = other.fp_;    /* elveszi a tömböt */
        other.fp_ = nullptr;
    }

    FilePtr& operator=(FilePtr&& rhs)
    {
        if (this != &rhs)
        {
            if(fp_ != nullptr)
                fclose(fp_);
            filename_ = rhs.filename_;
            fp_ = rhs.fp_;    /* elveszi a tömböt */
            rhs.fp_ = nullptr;
        }
        return *this;
    }

private:
    FILE* fp_;
    std::string filename_;

    void close_if_open() {
        if (fp_ != nullptr)
            fclose(fp_);
        fp_ = nullptr;
    }
};

/* ne lehessen ilyet csinálni (az operator FILE* miatt lehetne) */
void fclose(FilePtr) = delete;

FilePtr open_for_writing(char const* name)
{
    return FilePtr{ name, "wt" };
}



class Matrix 
{
private:
    size_t w_, h_;
    double* data_;

public:

    Matrix()
    {
        data_ = nullptr;
    }

    Matrix(size_t w, size_t h) : w_{ w }, h_{ h }
    {
        data_ = new double(w * h);
        for (size_t idx = 0; idx < w*h; idx++)
            data_[idx] = 0;
    }


    Matrix(const Matrix& other)
    {
        std::cout << "masolo" << std::endl;

        this->w_ = other.w_;
        this->h_ = other.h_;
        this->data_ = new double(w_ * h_);
        for (size_t idx = 0; idx < w_ * h_; idx++)
            data_[idx] = other.data_[idx];
    }
    Matrix& operator=(const Matrix& other)
    {
        std::cout << "ertekado" << std::endl;

        if (this != &other)
        {
            delete[] this->data_;
            this->w_ = other.w_;
            this->h_ = other.h_;
            this->data_ = new double(w_ * h_);
            for (size_t idx = 0; idx < w_ * h_; idx++)
                data_[idx] = other.data_[idx];
        }
        return *this;
    }
    Matrix(Matrix&& other)
    {
        std::cout << "mozgato" << std::endl;

        this->w_ = other.w_;
        this->h_ = other.h_;
        this->data_ = other.data_;
        other.data_ = nullptr;
    }
    Matrix& operator=(Matrix&& other)
    {
        std::cout << "mozgato ertekado" << std::endl;

        if (this != &other)
        {
            if (this != nullptr)
                delete[] this;
            this->w_ = other.w_;
            this->h_ = other.h_;
            this->data_ = other.data_;
            other.data_ = nullptr;
        }
        return *this;
    }
    ~Matrix()
    {
        if(data_ != nullptr)
            delete[] data_;
    }


    double& operator()(size_t x, size_t y)
    {
        size_t idx = (y - 1) * w_ + (x - 1);
        if (idx < 0 || idx >= w_ * h_)
            throw std::runtime_error("Index out of range");
        return data_[idx];
    }

    size_t width() { return w_; }
    size_t height() { return h_; }
};

std::ostream& operator<<(std::ostream& os, Matrix m)
{
    for (size_t c = 1; c <= m.width(); c++)
    {
        for (size_t r = 1; r <= m.height(); r++)
        {
            os << m(c, r) << " ";
        }
        os << std::endl;
    }
    return os;
}

int main() 
{
    Matrix m{ 3, 3 };
    m(1, 1) = 9;  m(2, 3) = 5;
    Matrix m2{ 5, 5 };
    std::cout << m(1, 1);

    //std::swap(m, m2);
    //std::cout << m;
}