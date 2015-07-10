import csv
import pygal

class Analyser(object):
	def __init__(self, db):
		self.rules = []
		self.profit = [0]
		self.all_profits = []

		with open(db) as dbfile:
			if(db.split(".")[-1] == 'csv'):
				self.matches = [row for row in csv.reader(dbfile) if self.is_valid(row)]

	def clear(self):
		self.rules = []
		self.profit = [0]
		self.all_profits = []

	def add_rule(self, bet_value, percents, formats):
		assert isinstance(bet_value, int)
		assert isinstance(percents, tuple)
		assert isinstance(formats, (tuple, str))

		percents = [x for x in range(percents[0], percents[1]+1)]

		self.rules.append([bet_value, percents, formats])

	def is_valid(self, match):
		return '(win)' in match[1] or '(win)' in match[4]

	def winner_stats(self, match):
		if '(win)' in match[1]: return (int(match[2][0:-1]), float(match[3]))
		if '(win)' in match[4]: return (int(match[5][0:-1]), float(match[6]))

	def loser_stats(self, match):
		if '(win)' not in match[1]: return (int(match[2][0:-1]), float(match[3]))
		if '(win)' not in match[4]: return (int(match[5][0:-1]), float(match[6]))

	def analyse(self):
		for rule in self.rules:
			for match in self.matches:
				winner = self.winner_stats(match)
				loser = self.loser_stats(match)

				if match[0] in rule[2]:
					if winner[0] in rule[1]:
						self.profit.append(self.profit[-1] + rule[0] * winner[1])
					elif loser[0] in rule[1]:
						self.profit.append(self.profit[-1] - rule[0])
					else:
						self.profit.append(self.profit[-1])
				else:
					self.profit.append(self.profit[-1])

			self.all_profits.append(self.profit)
			self.profit = [0]

	def abbr_formats(self, formats):
		final_str = ""

		if type(formats) == str:
			final_str = "BO" + formats[-1]
			return final_str
		else:
			for format in formats:
				final_str += "BO"
				final_str += format[-1] + "-"

			return final_str[0:-2]

	def export(self, title='Results', out='output.csv'):
		if out.split(".")[-1] == 'svg':
			chart = pygal.Line()
			chart.title = title
			for rule, profits in zip(self.rules, self.all_profits):
				rule_str = "{0}, {1}%-{2}%".format(self.abbr_formats(rule[2]), rule[1][0], rule[1][-1])
				chart.add(rule_str, profits)

			chart.render_to_file(out)

		elif out.split(".")[-1] == 'csv':
			with open(out, 'ab+') as csvfile:
				csvfile.write('Formats, Percents, Profit after 1000 bets (in $)\n')
				final_profits = [x[-1] for x in self.all_profits]

				for rule, profits in zip(self.rules, final_profits):
					rule_str = "{0},{1}%-{2}%,{3}\n".format(self.abbr_formats(rule[2]), rule[1][0], rule[1][-1], profits)
					csvfile.write(rule_str)