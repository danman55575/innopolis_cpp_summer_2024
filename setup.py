from setuptools import setup, Extension

def main():
    setup(
        name="cjson",
        version="0.5",
        author="D.R. Fathutdinov",
        date="17.07.2024",
        ext_modules=[Extension("cjson", ["cjson.cpp"])]
    )

if __name__ == "__main__":
    main()
