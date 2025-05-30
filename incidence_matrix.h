/* ����������� ������� �1 */

#ifndef INCIDENCE_MATRIX_H
#define INCIDENCE_MATRIX_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>

/**
 * ������� ��� ���������� ������� ������������� �����.
 *
 * @param inputFileName ��� �������� �����, ����������� ������� ���������.
 * @param outputFileName ��� ��������� �����, � ������� ����� �������� ������� �������������.
 * @throw std::invalid_argument ���� ������� ������ �����������.
 */
void BuildIncidenceMatrix(const std::string& inputFileName, const std::string& outputFileName);

#endif // INCIDENCE_MATRIX_H
