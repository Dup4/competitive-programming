
template <class InputIterator, class Function>
void my_for_each(InputIterator l, InputIterator r, Function f) {
	for (; l != r; ++l) {
		f(*l);
	}
}
