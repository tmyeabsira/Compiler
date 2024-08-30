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

    def print_tree(self, level=0):
        indent = " " * (4 * level)
        if isinstance(self.value, float):
            print(f"{indent}{self.value}")
        else:
            print(f"{indent}{self.value}")
            if self.left:
                self.left.print_tree(level + 1)
            if self.right:
                self.right.print_tree(level + 1)

class Parser:
    def __init__(self, tokens):
        self.tokens = tokens
        self.pos = 0

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
            self.expect(')')
            return node
        elif token.replace('.', '', 1).isdigit():
            self.advance()
            return Node(float(token))

    def current_token(self):
        return self.tokens[self.pos] if self.pos < len(self.tokens) else None

    def advance(self):
        self.pos += 1

    def expect(self, token):
        if self.current_token() == token:
            self.advance()
        else:
            raise SyntaxError(f"Expected {token} but found {self.current_token()}")

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

    print("Abstract Syntax Tree:")
    parse_tree.print_tree()

    result = parse_tree.evaluate()
    print(f"\nExpression: {expression}")
    print(f"Result: {result}")

