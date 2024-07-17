import cjson

import json

import ujson

import time


def getFromJson(json_str: str) -> dict:
    start = time.time()
    res = json.loads(json_str)
    print(f"The json library loaded the file for {time.time() - start} seconds")
    return res


def getFromCJson(json_str: str) -> dict:
    start = time.time()
    res = cjson.loads(json_str)
    print(f"The cjson library loaded the file for {time.time() - start} seconds")
    return res


def getFromUJson(json_str: str) -> dict:
    start = time.time()
    res = ujson.loads(json_str)
    print(f"The ujson library loaded the file for {time.time() - start} seconds")
    return res


def convertToJson(json_dict: dict) -> str:
    start = time.time()
    res = json.dumps(json_dict)
    print(f"The json library dumped the json file for {time.time() - start} second")
    return res


def convertToCJson(json_dict: dict) -> str:
    start = time.time()
    res = cjson.dumps(json_dict)
    print(f"The cjson library dumped the json file for {time.time() - start} second")
    return res


def convertToUJson(json_dict: dict) -> str:
    start = time.time()
    res = ujson.dumps(json_dict)
    print(f"The ujson library dumped the json file for {time.time() - start} second")
    return res


def correctness_test_1() -> None:
    print("RUN correctness_test_1...")
    json_str = ""
    with open("test1.json", "r", encoding="utf-8") as file:
        for line in file:
            json_str += line
    json_dict = json.loads(json_str)
    ujson_dict = ujson.loads(json_str)
    cjson_dict = cjson.loads(json_str)
    assert(json_dict == ujson_dict == cjson_dict)
    print("...correctness_test_1 PASSED\n")


def correctness_test_2() -> None:
    print("RUN correctness_test_2...")
    json_str = ""
    with open("test2.json", "r", encoding="utf-8") as file:
        for line in file:
            json_str += line
    json_dict = json.loads(json_str)
    ujson_dict = ujson.loads(json_str)
    cjson_dict = cjson.loads(json_str)
    assert(json_dict == ujson_dict == cjson_dict)
    assert(json.dumps(json_dict) == cjson.dumps(json_dict))
    print("...correctness_test_2 PASSED\n")


def correctness_test_3() -> None:
    print("RUN correctness_test_3...")
    json_str = ""
    with open("test3.json", "r", encoding="utf-8") as file:
        for line in file:
            json_str += line
    json_dict = json.loads(json_str)
    ujson_dict = ujson.loads(json_str)
    cjson_dict = cjson.loads(json_str)
    assert(json_dict == ujson_dict == cjson_dict)
    assert(json.dumps(json_dict) == cjson.dumps(json_dict))
    print("...correctness_test_3 PASSED\n")


def effectiveness_loads_test_1() -> None:
    print("RUN effectiveness_loads_test_1...")
    json_str = ""
    with open("test1.json", "r", encoding="utf-8") as file:
        for line in file:
            json_str += line
    json_dict = getFromJson(json_str)
    cjson_dict = getFromCJson(json_str)
    ujson_dict = getFromUJson(json_str)
    assert(json_dict == cjson_dict == ujson_dict)
    print("...effectiveness_loads_test_1 PASSED\n")


def effectiveness_loads_test_2() -> None:
    print("RUN effectiveness_loads_test_2...")
    json_str = ""
    with open("test2.json", "r", encoding="utf-8") as file:
        for line in file:
            json_str += line
    json_dict = getFromJson(json_str)
    cjson_dict = getFromCJson(json_str)
    ujson_dict = getFromUJson(json_str)
    assert(json_dict == cjson_dict == ujson_dict)
    print("...effectiveness_loads_test_2 PASSED\n")


def effectiveness_loads_test_3() -> None:
    print("RUN effectiveness_loads_test_3...")
    json_str = ""
    with open("test3.json", "r", encoding="utf-8") as file:
        for line in file:
            json_str += line
    json_dict = getFromJson(json_str)
    cjson_dict = getFromCJson(json_str)
    ujson_dict = getFromUJson(json_str)
    assert(json_dict == cjson_dict == ujson_dict)
    print("...effectiveness_loads_test_3 PASSED\n")


def effectiveness_dumps_test_1() -> None:
    print("RUN effectiveness_dumps_test_1...")
    json_str = ""
    with open("test1.json", "r", encoding="utf-8") as file:
        for line in file:
            json_str += line
    json_dict = ujson.loads(json_str)
    json_str = convertToJson(json_dict)
    cjson_str = convertToCJson(json_dict)
    ujson_str = convertToUJson(json_dict)
    assert(json_str == cjson_str)
    print("...effectiveness_dumps_test_1 PASSED\n")


def effectiveness_dumps_test_2() -> None:
    print("RUN effectiveness_dumps_test_2...")
    json_str = ""
    with open("test2.json", "r", encoding="utf-8") as file:
        for line in file:
            json_str += line
    json_dict = ujson.loads(json_str)
    json_str = convertToJson(json_dict)
    cjson_str = convertToCJson(json_dict)
    ujson_str = convertToUJson(json_dict)
    assert(json_str == cjson_str)
    print("...effectiveness_dumps_test_2 PASSED\n")


def effectiveness_dumps_test_3() -> None:
    print("RUN effectiveness_dumps_test_3...")
    json_str = ""
    with open("test3.json", "r", encoding="utf-8") as file:
        for line in file:
            json_str += line
    json_dict = ujson.loads(json_str)
    json_str = convertToJson(json_dict)
    cjson_str = convertToCJson(json_dict)
    ujson_str = convertToUJson(json_dict)
    assert(json_str == cjson_str)
    print("...effectiveness_dumps_test_3 PASSED\n")


def main():
    correctness_test_1()
    correctness_test_2()
    correctness_test_3()
    effectiveness_loads_test_1()
    effectiveness_loads_test_2()
    effectiveness_loads_test_3()
    effectiveness_dumps_test_1()
    effectiveness_dumps_test_2()
    effectiveness_dumps_test_3()


if __name__ == "__main__":
    main()
