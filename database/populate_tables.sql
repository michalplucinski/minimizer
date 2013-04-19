INSERT INTO atom(atomic_number, ionic_radius) VALUES
   (1, 1.4)
  ,(2, 1.6)
  ,(6, 2.2)
  ;

-- Always make sure first_atomic_number is LTE the second_atomic_number to avoid repetition
INSERT INTO bond(first_atomic_number, second_atomic_number, dissociation_energy) VALUES
   (1, 2, 5.2)
  ,(1, 3, 5.3)

  ,(2, 3, 4.4)
  ,(2, 4, 3.5)

  ,(3, 3, 3.9)
  ;