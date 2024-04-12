#include<cstdio>

class FilePtr
{
public:
    FilePtr() { f_ = nullptr; }

    FilePtr(FilePtr& fp) = delete;
    FilePtr& operator=(FilePtr& fp) = delete;

    void operator=(FILE* f)
    {
        f_ = f;
    }

    operator FILE*()
    {
        return f_;
    }


    ~FilePtr()
    {
        fclose(f_);
    }

private:
    FILE* f_;
};

void fclose(FilePtr)
{
    //#error "This code should not compile"
}

int main4() {
    FilePtr fp;

    fp = fopen("hello.txt", "wt");
    fprintf(fp, "Hello vilag");
}