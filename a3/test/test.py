#!/usr/bin/env python3
import json
import sys
import os

def emit_cpp_from_json(data):
    lines = []
    for modname, modinfo in data.items():
        lines.append(f'struct module* mod = make_module("{modname}");\n')

        for func in modinfo.get("functions", []):
            funcname = func["name"]
            lines.append(f'struct function* func_{funcname} = make_function("{funcname}");')


            for bb in func.get("basic_blocks", []):
                bbname = bb["name"]
                entry_flag = 1 if bb.get("type") == "entry" else 0
                lines.append(f'struct basic_block* bb_{bbname} = make_bb("{bbname}");')

                lines.append(
                    f'try {{ func_{funcname}->insert_bb(bb_{bbname}, {entry_flag}); }} '
                    f'catch (const std::exception& e) {{ std::cout << e.what() << "\\n"; }}'
                )


            for link in func.get("links", []):
                from_bb = link["from"]
                to_bb = link["to"]
                tag = link["tag"]
                lines.append(
                    f'try {{ bb_{from_bb}->add_sucessor(bb_{to_bb}, "{tag}"); }} '
                    f'catch (const std::exception& e) {{ std::cout << e.what() << "\\n"; }}'
                )

            lines.append(
                f'try {{ mod->insert_func(func_{funcname}); }} '
                f'catch (const std::exception& e) {{ std::cout << e.what() << "\\n"; }}'
            )

            lines.append("delete mod;")
            lines.append("")

    return "\n    ".join(lines)

def main():

    json_file = sys.argv[1]
    template_file = "testtemplate"

    with open(json_file, "r") as jf:
        data = json.load(jf)

    emitted_code = emit_cpp_from_json(data)

    with open(template_file, "r") as tf:
        template_content = tf.read()

    output_code = template_content.format(emitted_code)

    base_name = os.path.splitext(os.path.basename(json_file))[0]
    output_file = f"{base_name}.cc"

    with open(output_file, "w") as out:
        out.write(output_code)

    print(f" Generated C++ test file: {output_file}")

if __name__ == "__main__":
    main()
