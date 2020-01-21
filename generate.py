import json
from jinja2 import Environment, FileSystemLoader



def load_old_verify_results(path: str):
    try:
        return json.load(open(path, 'r'))
    except Exception as e:
        print(str(e))
        return {}

if __name__ == '__main__':
    verify_results = load_old_verify_results(".ds_verify/verify_results.json")

    verify_targets = {}
    verify_errors = {}

    for verify_name, result in verify_results.items():
        if result['status'] == 'OK':
            for detail in result['detail']:
                detail['source_path'] = result['source_path']
                detail['query'] = json.dumps(detail['query'], indent=2)
                if detail['status'] == 'failure':
                    detail['fail_query'] = detail['fail_at']['fail_query']
                    detail['fail_info'] = detail['fail_at']['fail_info']
                if detail['target'] not in verify_targets:
                    verify_targets[detail['target']] = []
                verify_targets[detail['target']].append(detail)
        else:
            verify_errors[verify_name] = str(result.detail)

    print(str(verify_targets))
    print(str(verify_errors))
    env = Environment(loader=FileSystemLoader('./templates', encoding='utf8'))
    index = env.get_template('index.html')
    targets = [{"name": name, "details": sorted(details, key=lambda d: d['test_case'])} for name, details in verify_targets.items()]
    print(targets)
    open("docs/index.html", 'w').write(index.render(targets=targets))




