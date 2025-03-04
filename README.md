# SenseVoice.cpp: Qt & Python Bindings

SenseVoice.cpp C++ 库，支持 Qt 接口和 Python Bindings。

特别致谢：[lovemefan/SenseVoice.cpp](https://github.com/lovemefan/SenseVoice.cpp)

项目遵循 MIT 许可证。

Clone this project:

```shell
git clone https://github.com/SSRVodka/sense-voice.cpp.git
git submodule sync && git submodule update --init --recursive
```

Python Conda 包编译：

```shell
conda build . -c conda-forge
```

Python Pip 包编译和测试：

```shell
python3 setup.py bdist_wheel
# Choose an environment & install
pip install dist/<pkg_name>.whl
# Run import test
python3 pytest/test.py
```



SenseVoice.cpp library (C++) supports Qt interface & Python bindings.

Special thanks to [lovemefan/SenseVoice.cpp](https://github.com/lovemefan/SenseVoice.cpp).

The project is under the MIT license.
