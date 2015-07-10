from databasebuilder import DatabaseBuilder
from analyser import Analyser

if __name__ == "__main__":
	try:
		assert open('db.csv')
	except IOError:
		print "DB needs to be generated...",
		b = DatabaseBuilder(matches=1000)
		b.generate_db('csv')

	a = Analyser(db='db.csv')
	a.add_rule(bet_value=100, percents=(75,100), formats=('Best of 5', 'Best of 3'))
	a.add_rule(bet_value=100, percents=(10,30), formats=('Best of 1'))
	a.analyse()
	a.plot('out.svg')