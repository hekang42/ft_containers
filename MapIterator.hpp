#if !defined(MAPITERATOR_HPP)
# define MAPITERATOR_HPP
class MapIterator
{
private:
	/* data */
public:
	MapIterator(/* args*/);
	MapIterator(const MapIterator &other){};
	MapIterator &operator=(const MapIterator &other){};
	~MapIterator();
};

#endif // MAPITERATOR_HPP