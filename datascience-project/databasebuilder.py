import csv
import urllib2

class DatabaseBuilder(object):
	def __init__(self, matches=50):
		assert type(matches) == int
		self.matches_needed = matches
		self.LOUNGE_LINK = 'http://csgolounge.com/'
		self.LOUNGE_MATCH_LINK = 'http://csgolounge.com/match?m='
		self.first_match_id = None
		self.success = False
		self.matches = []

	def find_first_match(self):
		try:
			src = urllib2.urlopen(self.LOUNGE_LINK).read()
			first_match = src.split('<div class="matchheader">')[1]
			self.first_match_id = int(first_match.split('<a href="match?m=')[1].split('"')[0])
		except IOError:
			print "First match parsing failed, retrying..."
			return False

	def average_ratio(self, ratio):
		if not 'to' in ratio:
			return ratio
		else:
			ratio1 = float(ratio.split(' to ')[0])
			ratio2 = float(ratio.split(' to ')[1])
			return float(str((ratio1 + ratio2) / 2)[0:4])

	def parse_match(self, id):
			print "Parsing match #{0}...".format(id),

			try:
				m = urllib2.urlopen(self.LOUNGE_MATCH_LINK + str(id)).read()
				format = m.split('center;width: 28%;">')[1].split('<')[0]
				team1 = m.split('      <b>')[1].split("<")[0]
				team2 = m.split('      <b>')[2].split("<")[0]
				team1_percents = m.split("</b><br><i>")[1].split("<")[0]
				team2_percents = m.split("</b><br><i>")[2].split("<")[0]
				team1_ratio = self.average_ratio(m.split('Value<br>')[1].split(' for')[0])
				team2_ratio = self.average_ratio(m.split('Value<br>')[2].split(' for')[0])

				print "done"

				return [format, team1, team1_percents, team1_ratio, team2, team2_percents, team2_ratio]
			except IOError:
				print "failed"
				return 0
			except:
				print "failed"
				return 1

	def generate_db(self, output_type):
		assert type(output_type) == str

		self.find_first_match()
		while not self.first_match_id:
			self.find_first_match()

		parsed_matches = 0
		match_id = self.first_match_id

		while parsed_matches < self.matches_needed:
			match_info = self.parse_match(match_id)
			while match_info == 0:
				match_info = self.parse_match(match_id)

			if(match_info != 1):
				self.matches.append(match_info)
				parsed_matches += 1

			match_id -= 1

		if output_type == 'csv':
			with open("db.csv", "wb") as f:
				writer = csv.writer(f)
				writer.writerows(self.matches)