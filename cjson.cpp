#include <python3.10/Python.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <map>

class ParseJson {
 private:
    const std::string& text;
    size_t number_of_pairs;
    size_t start_idx;
    size_t end_idx;

    void goToSym() {
        while (start_idx < end_idx) {
            char sym = text[start_idx];
            if (' ' == sym || '\n' == sym || '\t' == sym) {
                start_idx += 1;
            } else {
                return;
            }
        }
    }

    PyObject* buildStrObject() {
        if (start_idx == end_idx || text[start_idx] != '"') {
            throw std::invalid_argument("Expected a string");
        }
        start_idx += 1;

        std::string word = "";

        while (start_idx < end_idx) {
            if (text[start_idx] == '"') {
                break;
            }
            word.push_back(text[start_idx]);
            start_idx += 1;
        }

        if (start_idx == end_idx) {
            throw std::invalid_argument("Unexpected end of the string");
        }

        start_idx += 1;
        PyObject* obj;
        if (!(obj = Py_BuildValue("s", word.data()))) {
            throw std::runtime_error(
                "ERROR: Failed to build string value\n");
        }
        return obj;
    }

    PyObject* buildNumObject() {
        std::string num = "";

        if (text[start_idx] == '-') {
            num.push_back('-');
            start_idx += 1;
        }

        while (start_idx < end_idx) {
            char sym = text[start_idx];
            if ('0' <= sym && sym <= '9') {
                num.push_back(text[start_idx]);
                start_idx += 1;
            } else if (
                sym == ' ' || sym == '\n' ||
                sym == '\t' || sym == ',') {
                break;
            } else {
                throw std::invalid_argument("Invalid json syntax");
            }
        }

        if (num.size() > 9) {
            throw std::invalid_argument("Too big number in json");
        }
        if (num.size() == 1 && num[0] == '-') {
            throw std::invalid_argument("Invalid json syntax");
        }

        PyObject* obj;
        int intValue = std::stoi(num);
        if (!(obj = Py_BuildValue("i", intValue))) {
            throw std::runtime_error(
                "ERROR: Failed to build integer value\n");
        }
        return obj;
    }

    void checkDelimiter() {
        if (start_idx < end_idx && text[start_idx] == ':') {
            start_idx += 1;
        } else {
            throw std::invalid_argument("Symbol ':' was expected");
        }
    }

    void checkComma() {
        if (number_of_pairs == 0) {
            return;
        }
        if (start_idx < end_idx && text[start_idx] == ',') {
            start_idx += 1;
        } else {
            throw std::invalid_argument("Symbol ',' was expected");
        }
    }

    void setPair(PyObject* dict) {
        PyObject *key = NULL;
        PyObject *value = NULL;

        checkComma();

        goToSym();
        key = buildStrObject();

        goToSym();
        checkDelimiter();

        goToSym();
        if (start_idx == end_idx) {
            throw std::invalid_argument("Unexpected end of the string");
        }

        if (
            ('0' <= text[start_idx] && text[start_idx] <= '9') ||
            text[start_idx] == '-') {
            value = buildNumObject();
        } else {
            value = buildStrObject();
        }

        if (PyDict_SetItem(dict, key, value) < 0) {
            throw std::runtime_error(
                "ERROR: Failed to set item\n");
        }

        number_of_pairs += 1;
    }

 public:
    explicit ParseJson(const std::string& json_str): text(json_str) {
        if (text[0] != '{' || text[text.size() - 1] != '}') {
            throw std::invalid_argument("Invalid json syntax");
        }
        this->number_of_pairs = 0;
        this->start_idx = 1;
        this->end_idx = text.size() - 1;
    }

    void parse(PyObject* dict) {
        if (text.size() == 2) {
            return;
        }

        number_of_pairs = 0;
        start_idx = 1;
        goToSym();
        while (start_idx < end_idx) {
            setPair(dict);
            goToSym();
        }
    }
};

PyObject* loads_json(PyObject* self, PyObject* args) {
    char* ptr_to_text;
    if (!PyArg_ParseTuple(args, "s", &ptr_to_text)) {
        throw std::runtime_error(
            "Failed to parse arguments\n");
    }
    std::string text = ptr_to_text;

    PyObject* dict = NULL;
    if (!(dict = PyDict_New())) {
        throw std::runtime_error(
            "ERROR: Failed to create Dict Object\n");
    }

    ParseJson parser(text);
    parser.parse(dict);

    return dict;
}

PyObject* dumps_json(PyObject* self, PyObject* args) {
    std::string ans = "{";

    PyObject* dict;
    if (!(PyArg_ParseTuple(args, "O!", &PyDict_Type, &dict))) {
        throw std::runtime_error(
            "ERROR: Failed to parse Dict Object\n");
    }

    PyObject *key, *value;
    Py_ssize_t pos = 0;
    bool isFirstItem = true;

    while (PyDict_Next(dict, &pos, &key, &value)) {
        PyObject* key_repr = PyObject_Repr(key);
        PyObject* value_repr = PyObject_Repr(value);
        PyObject* obj_key = PyUnicode_AsEncodedString(
            key_repr, "utf-8", "~E~");
        PyObject* obj_value = PyUnicode_AsEncodedString(
            value_repr, "utf-8", "~E~");
        const char* str_key = PyBytes_AS_STRING(obj_key);
        const char* str_value = PyBytes_AS_STRING(obj_value);
        if (!isFirstItem) {
            ans += ", ";
        }
        isFirstItem = false;

        if (*str_key == '\'') {
            ans.push_back('"');
            str_key++;
        }
        while (*str_key != '\0') {
            ans.push_back(*str_key);
            str_key++;
        }
        str_key--;
        if (*str_key == '\'') {
            ans.pop_back();
            ans.push_back('"');
        }

        ans += ": ";

        if (*str_value == '\'') {
            str_value++;
            ans.push_back('"');
        }
        while (*str_value != '\0') {
            ans.push_back(*str_value);
            str_value++;
        }
        str_value--;
        if (*str_value == '\'') {
            ans.pop_back();
            ans.push_back('"');
        }
    }

    ans.push_back('}');

    PyObject* res = Py_BuildValue("s", ans.data());
    return res;
}

static PyMethodDef module_funcs[] = {
  {"loads", loads_json, METH_VARARGS,
  "Convert json string to python data structures"},
  {"dumps", dumps_json, METH_VARARGS,
  "Convert python dict to json string"},
  {NULL, NULL, 0, NULL}
};

static PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "cjson",
    "Module with method for working with json",
    -1,
    module_funcs,
};

PyMODINIT_FUNC PyInit_cjson() {
    return PyModule_Create(&module);
}
