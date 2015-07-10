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
	for i in range(5,51):
		a.add_rule(bet_value=100, percents=(0,i), formats=('Best of 5', 'Best of 3', 'Best of 1'))
		a.add_rule(bet_value=100, percents=(0,i), formats=('Best of 5', 'Best of 3'))
		a.add_rule(bet_value=100, percents=(0,i), formats=('Best of 5'))
		a.add_rule(bet_value=100, percents=(0,i), formats=('Best of 3'))
		a.add_rule(bet_value=100, percents=(0,i), formats=('Best of 1'))

	for i in range(50,95):
		a.add_rule(bet_value=100, percents=(i,100), formats=('Best of 5', 'Best of 3', 'Best of 1'))
		a.add_rule(bet_value=100, percents=(i,100), formats=('Best of 5', 'Best of 3'))
		a.add_rule(bet_value=100, percents=(i,100), formats=('Best of 5'))
		a.add_rule(bet_value=100, percents=(i,100), formats=('Best of 3'))
		a.add_rule(bet_value=100, percents=(i,100), formats=('Best of 1'))

	a.analyse()
	#a.export(title='All betting results', out='overall.svg')
	a.export(out='overall.csv')