#ifndef MOVIE_H
#define MOVIE_H

#include <fstream>
#include <iostream>
#include <map>

using namespace std;

class Movie;

class MovieFactory {
public:
  // Creates a new Movie object based on given movie type
  // Movie object is initialized with data from given input file
  virtual Movie *create(ifstream &file, char movieType) const = 0;

  // Creates a new Movie object (with sorting attributes) based on given
  // movieTypetype
  // Movie object is initialized with data from given input file
  // Returns pointer to Movie object is successfully created and initialized,
  // otherwise nullptr
  virtual Movie *createPartial(ifstream &file, char movieType) = 0;
};

class Movie {
  // Overloaded operator<< to print movie details
  friend ostream &operator<<(ostream &os, const Movie &movie);

public:
  // Destructor
  virtual ~Movie() = default;

  // Reads and parses movie data from given file
  // Movie object is initialized with data from given input file
  virtual void setData(ifstream &file);

  // Getter for movie type
  const char &getMovieType() const;

  // Getter for stock
  const int &getStock() const;

  // Getter for director
  const string &getDirector() const;

  // Getter for title
  const string &getTitle() const;

  // Getter for release year
  const int &getReleaseYear() const;

  // Getter for major actor
  const string &getMajorActor() const;

  // Getter for release month
  const int &getReleaseMonth() const;

  // Getter for total stock (to calculate # of movies borrowed)
  const int &getTotalStock() const;

  // Setter for movie type
  void setMovieType(char movieType);

  // Setter for stock
  void setStock(int stock);

  // Setter for director
  void setDirector(string director);

  // Setter for title
  void setTitle(string title);

  // Setter for release year
  void setReleaseYear(int releaseYear);

  // Setter for major actor
  void setMajorActor(string majorActor);

  // Setter for release month
  void setReleaseMonth(int month);

  // Operator= to copy given Movie object
  virtual Movie &operator=(Movie &copy);

  // Compares 2 movies based on specified criteria
  // Returns true if this movie is less than other, false otherwise
  virtual bool operator<(const Movie &other) const = 0;

  // Compares 2 movies based on specified criteria
  // Returns true if this movie is greater than other, false otherwise
  virtual bool operator>(const Movie &other) const = 0;

  // Compares equality of 2 movies
  // Returns true if 2 movies are equal to each other, false otherwise
  virtual bool operator==(const Movie &other) const = 0;

  // Register a concrete factory with a given movie type
  static void registerType(const char &movieType, MovieFactory *factory);

  // Find the corresponding Movie factory and get factory to create the object
  static Movie *create(ifstream &file, char movieType);

  // Find the corresponding Movie factory and get factory to create the partial
  // object (with sorting attributes)
  static Movie *createPartial(ifstream &file, char movieType);

protected:
  // Pure virtual method to print movie details
  // Helper method for overloaded operator<<
  virtual ostream &printer(ostream &os) const = 0;

private:
  char movieType;
  string director, title, majorActor;
  int totalStock, stock, releaseMonth, releaseYear;

  /**
   * Storage place for the concrete movie factories
   * Having it available only through this function guarantees that
   * this static variable is initialized
   * when a concrete factory tries to register itself
   * @return map
   */
  static map<char, MovieFactory *> &getMap();
};

#endif
