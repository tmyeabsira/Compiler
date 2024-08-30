class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self.left = left
        self.right = right

    def evaluate(self):
        if isinstance(self.value, float):  # Leaf node (number)
            return self.value
        elif self.value == '+':
            return self.left.evaluate() + self.right.evaluate()
        elif self.value == '-':
            return self.left.evaluate() - self.right.evaluate()
        elif self.value == '*':
            return self.left.evaluate() * self.right.evaluate()
        elif self.value == '/':
            return self.left.evaluate() / self.right.evaluate()

class Parser:
    def __init__(self, tokens):
        self.tokens = tokens
        self.pos = 0
        self.error_flag = False

    def parse(self):
        return self.expr()

    def expr(self):
        node = self.term()
        while self.current_token() in ('+', '-'):
            op = self.current_token()
            self.advance()
            node = Node(op, left=node, right=self.term())
        return node

    def term(self):
        node = self.factor()
        while self.current_token() in ('*', '/'):
            op = self.current_token()
            self.advance()
            node = Node(op, left=node, right=self.factor())
        return node

    def factor(self):
        token = self.current_token()
        if token == '(':
            self.advance()
            node = self.expr()
            if self.current_token() == ')':
                self.advance()
            else:
                self.report_error("Expected ')'")
                self.panic_mode(')')
            return node
        elif token and token.replace('.', '', 1).isdigit():
            self.advance()
            return Node(float(token))
        else:
            self.report_error("Expected number or '('")
            self.panic_mode(')')
            return Node(0.0)  # Insert a default value for recovery

    def current_token(self):
        return self.tokens[self.pos] if self.pos < len(self.tokens) else None

    def advance(self):
        if self.pos < len(self.tokens):
            self.pos += 1

    def report_error(self, message):
        self.error_flag = True
        print(f"Syntax error at token '{self.current_token()}': {message}")

    def panic_mode(self, recovery_token):
        # Skip tokens until we find the recovery token
        while self.current_token() and self.current_token() != recovery_token:
            self.advance()
        self.advance()  # Consume the recovery token

def tokenize(expression):
    tokens = []
    num_buffer = []
    for char in expression:
        if char.isdigit() or char == '.':
            num_buffer.append(char)
        else:
            if num_buffer:
                tokens.append(''.join(num_buffer))
                num_buffer = []
            if char in '+-*/()':
                tokens.append(char)
    if num_buffer:
        tokens.append(''.join(num_buffer))
    return tokens

# Main program
if __name__ == "__main__":
    expression = input("Enter an arithmetic expression: ")
    tokens = tokenize(expression)
    parser = Parser(tokens)
    parse_tree = parser.parse()

    if not parser.error_flag:
        result = parse_tree.evaluate()
        print(f"Expression: {expression}")
        print(f"Result: {result}")
    else:
        print("Could not evaluate expression due to syntax errors.")

