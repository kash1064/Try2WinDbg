import base64

texts = [
    "AAA",
    "TEST",
    "this is test",
    "Hello",
    "Fan-Fan-Fun!!",
]

base64_type = "BASE64_TYPE_STANDARD"
content = "static const BASE64_TEST BASE64_TESTS[] = {\n"
for base_text in texts:
    text_length = len(base_text)
    expect_text = base64.b64encode(base_text.encode()).decode()
    content += "{"
    content += "{},      \"{}\", {}, \"{}\"".format(base64_type, base_text, text_length, expect_text)
    content += "},\n"
content += "};"

print(content)