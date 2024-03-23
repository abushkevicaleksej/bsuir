#include "TruthTable.h"

int IsOperator(char c)
{
    switch (c)
    {
    case '!':
    case '&':
    case '|':
    case '>':
        return 1;
    }
    return 0;
}
int IsBinaryOperator(char c)
{
    return c != '!' && IsOperator(c);
}
int IsInvalidChar(char c)
{
    if (c == '(' || c == ')')
        return 0;
    else if (isupper(c) || IsOperator(c))
        return 0;
    return 1;
}
int IsUpperAlpha(char c)
{
    return isupper(c);
}
int Priority(char operation)
{
    switch (operation)
    {
    case '!':
        return 5;
    case '&':
        return 4;
    case '|':
        return 3;
    case '>':
        return 2;
    default:
        return 0;
    }
}

int IsValidExpression(const string& expression)
{
    if (expression.empty())
    {
        throw std::invalid_argument("You didn't enter anything!");
    }

    string::const_iterator pos;
    pos = find_if(expression.begin(), expression.end(), IsInvalidChar);
    if (pos != expression.end())
    {
        throw std::invalid_argument("Invalid characters: '" + string(1, *pos) + "'");
    }
    vector<int> bracketpos[2];
    for (pos = expression.begin(); pos != expression.end(); ++pos)
    {
        if (*pos == '(')
            bracketpos[0].push_back(distance(expression.begin(), pos));
        else if (*pos == ')')
            bracketpos[1].push_back(distance(expression.begin(), pos));
    }
    vector<int>::size_type vector;
    for (vector = 0; vector != bracketpos[0].size(); ++vector)
    {
        if (bracketpos[0][vector] > bracketpos[1][vector])
        {
            throw std::invalid_argument("Bracket positions don't match!");
        }
    }
    return 1;
}


set<char> GetExpressionInfo(const string& expression)
{
    set<char> expression_elem;

    for (string::size_type i = 0; i != expression.size(); ++i)
    {
        if (isupper(expression[i]))
        {
            expression_elem.insert(expression[i]);
        }
    }
    return expression_elem;
}

string InfixToSuffix(const string& expression)
{
    char top;
    stack<char> stack;
    string suffix;

    for (string::size_type i = 0; i != expression.size(); ++i)
    {
        if (isupper(expression[i]))
            suffix += expression[i];
        else if (expression[i] == '(')
            stack.push(expression[i]);
        else if (IsOperator(expression[i]))
        {
            while (1)
            {
                if (stack.empty() || stack.top() == '(')
                {
                    stack.push(expression[i]);
                    break;
                }
                else
                {
                    top = stack.top();
                    if (Priority(expression[i]) > Priority(top) || (expression[i] == '!' && top == '!'))
                    {
                        stack.push(expression[i]);
                        break;
                    }
                    else
                    {
                        suffix += stack.top();
                        stack.pop();
                    }
                }
            }
        }
        else if (expression[i] == ')')
        {
            while (!stack.empty() && (top = stack.top()) != '(')
            {
                suffix += top;
                stack.pop();
            }
            stack.pop();
        }

    }
    while (!stack.empty())
    {
        suffix += stack.top();
        stack.pop();
    }
    return suffix;
}

int Eval(const string& row, const string& suffix, const set<char>& expression_elem)
{
    char intermediate = 0;
    int first, second, result;
    stack<char> stack;
    map<char, int> map;
    string::size_type i;

    set<char>::const_iterator pos;
    for (pos = expression_elem.begin(), i = 0; pos != expression_elem.end(); ++pos, ++i)
    {
        map.insert(pair<char, int>(*pos, row[i] - '0'));
    }

    first = second = 0;
    for (i = 0; i != suffix.size(); ++i)
    {
        if (isupper(suffix[i]))
            stack.push(map[suffix[i]]);
        else if (IsOperator(suffix[i]))
        {
            second = stack.top();
            stack.pop();

            if (suffix[i] != '!' && !stack.empty())
            {
                first = stack.top();
                stack.pop();
            }

            switch (suffix[i])
            {
            case '!':
                intermediate = !second;
                break;
            case '&':
                intermediate = first && second;
                break;
            case '|':
                intermediate = first || second;
                break;
            case '>':
                intermediate = !first || second;
                break;
            }
            stack.push(intermediate);
        }
    }
    result = stack.top();
    stack.pop();
    return result;
}

vector<char> PrintTable(const string& expression, vector<int>& index)
{
    int cols, rows, intermediate;
    string row, suffix;
    set<char> expression_elem;

    expression_elem = GetExpressionInfo(expression);
    for (set<char>::iterator pos = expression_elem.begin(); pos != expression_elem.end(); ++pos)
    {
        cout << '\t' << *pos;
    }
    cout << '\t' << expression << endl;

    suffix = InfixToSuffix(expression);
    cols = expression_elem.size();
    rows = static_cast<int>(pow(2.0, cols));

    bitset<26> bsize;
    vector<char> result;
    for (int i = 0; i < rows; ++i)
    {
        bsize = i;
        row = bsize.to_string();
        row = bsize.to_string<char, char_traits<char>, allocator<char> >();
        row.erase(0, 26 - cols);
        for (int j = 0; j < cols; ++j)
        {
            cout << '\t' << row[j];
        }
        intermediate = Eval(row, suffix, expression_elem);
        result.push_back(intermediate);
        cout << '\t' << intermediate << endl;

        index.push_back(intermediate);
    }
    return result;
}

double CountIndexNumber(double &decimal, vector<int>&index)
{
    for (int i = 0; i < index.size(); i++)
    {
        decimal = decimal * 2 + index[i];
        cout << index[i] << " ";
    }
    cout << " = index = " << decimal << endl;
    return decimal;
}


int IsTautology(const vector<char>& result)
{
    return result.end() == find(result.begin(), result.end(), 0);
}

int IsContradiction(const vector<char>& result)
{
    return result.end() == find(result.begin(), result.end(), 1);
}


void PrintCnf(const vector<char>& result, const set<char>& expression_elem)
{
    if (IsTautology(result))
        return;

    vector<char> element;
    copy(expression_elem.begin(), expression_elem.end(), back_inserter(element));

    size_t i, j;
    vector<int> vector;
    for (i = 0; i != result.size(); ++i)
    {
        if (result[i] == 0)
            vector.push_back(i);
    }

    cout << "CNF\n" << "CNF Index Form (";
    for (i = 0; i != vector.size(); ++i)
    {
        if (i < vector.size() - 1)
            cout << vector[i] << ", ";
        else
            cout << vector[i];
    }
    cout << ')' << endl;

    bitset<26> bsize;
    string row;
    for (i = 0; i != vector.size(); ++i)
    {
        cout << '(';
        bsize = vector[i];
        row = bsize.to_string();
        row = bsize.to_string<char, char_traits<char>, allocator<char> >();
        row.erase(0, 26 - element.size());
        for (j = 0; j != element.size(); ++j)
        {
            if (row[j] == '1')
                cout << "!" << element[j];
            else
                cout << element[j];

            if (j < element.size() - 1)
                cout << " | ";
        }
        if (i < vector.size() - 1)
            cout << ") & ";
        else
            cout << ')' << endl;
    }
}

void PrintDnf(const vector<char>& result, const set<char>& expression_elem)
{
    if (IsContradiction(result))
        return;

    vector<char> element;
    copy(expression_elem.begin(), expression_elem.end(), back_inserter(element));

    size_t i, j;
    vector<int> vector;
    for (i = 0; i != result.size(); ++i)
    {
        if (result[i] == 1)
            vector.push_back(i);
    }

    cout << "DNF\n" << "DNF Index Form (";
    for (i = 0; i != vector.size(); ++i)
    {
        if (i < vector.size() - 1)
            cout << vector[i] << ", ";
        else
            cout << vector[i];
    }
    cout << ')' << endl;

    bitset<26> bsize;
    string row;
    for (i = 0; i != vector.size(); ++i)
    {
        cout << '(';
        bsize = vector[i];
        row = bsize.to_string<char, char_traits<char>, allocator<char> >();
        row.erase(0, 26 - element.size());
        for (j = 0; j != element.size(); ++j)
        {
            if (row[j] == '1')
                cout << element[j];
            else
                cout << "!" << element[j];

            if (j < element.size() - 1)
                cout << " & ";
        }
        if (i < vector.size() - 1)
            cout << ") | ";
        else
            cout << ')' << endl;
    }
}
