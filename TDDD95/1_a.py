"""Problem A: Help!"""
class Solver():
    def __init__(self, n: int):
        self.n = n #number of test cases
        self.patterns = []
        self.solutions = []
    
    def main(self):
        if self.n < 0: return
        self._get_test_cases()
        self._compare_patterns()
        self._print_solutions()
    
    def _print_solutions(self):
        for sol in self.solutions:
            print(sol)

    def _compare_patterns(self):
        for n, pattern_pair in enumerate(self.patterns):
            placeholders = {"pattern_one": {}, "pattern_two": {}}
            pattern_one: list[str] = pattern_pair[0]
            pattern_two: list[str] = pattern_pair[1]
            PATTERN_LENGTH = len(pattern_one)
            for i in range(PATTERN_LENGTH):
                if pattern_one[i].startswith("<") and pattern_two[i].startswith("<"):
                    continue
                if pattern_one[i].startswith("<"):
                    if pattern_one[i] in placeholders["pattern_one"]:
                        if placeholders["pattern_one"][pattern_one[i]] != pattern_two[i]:
                            self._kill_solution()
                            break
                    placeholders["pattern_one"][pattern_one[i]] = pattern_two[i]
                elif pattern_two[i].startswith("<"):
                    if pattern_two[i] in placeholders["pattern_two"]:
                        if placeholders["pattern_two"][pattern_two[i]] != pattern_one[i]:
                            self._kill_solution()
                            break
                    placeholders["pattern_two"][pattern_two[i]] = pattern_one[i]
            sol_one = " ".join(pattern_one)
            sol_two = " ".join(pattern_two)
            for placeholder in placeholders["pattern_one"]:
                sol_one = sol_one.replace(placeholder, placeholders["pattern_one"][placeholder])
            for placeholder in placeholders["pattern_two"]:
                sol_two = sol_two.replace(placeholder, placeholders["pattern_two"][placeholder])
            if sol_one == sol_two:
                self.solutions.append(sol_one)

    def _kill_solution(self):
        self.solutions.append("-")
    
    def _get_test_cases(self):
        for _ in range(self.n):
            pattern_one = self._read_input().split()
            pattern_two = self._read_input().split()
            assert len(pattern_one) == len(pattern_two), "Patterns must be of same length."
            self.patterns.append([pattern_one, pattern_two])

    def _read_input(self):
        pattern = input().lower()
        assert isinstance(pattern, str), "Input must be a string."
        assert 0 <= len(pattern) <= 100, "Input must be longer than 0, shorter than 100 characters."
        for word in pattern.split():
            assert len(word) <= 15, "Each word of pattern can be at most 15 charecters."
        return pattern


if __name__ == "__main__":
    n = int(input())
    assert isinstance(n, int), "Number of test cases must be an int."
    assert n <= 100, "Number of test cases cannot exceed 100."
    solver = Solver(n)
    solver.main()