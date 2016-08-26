/**
 * @file rp_tree_max_split.hpp
 * @author Mikhail Lozhnikov
 *
 * Definition of class (RPTreeMaxSplit) to split a binary space partition
 * tree.
 */
#ifndef MLPACK_CORE_TREE_BINARY_SPACE_TREE_RP_TREE_MAX_SPLIT_HPP
#define MLPACK_CORE_TREE_BINARY_SPACE_TREE_RP_TREE_MAX_SPLIT_HPP

#include <mlpack/core.hpp>
#include "perform_split.hpp"

namespace mlpack {
namespace tree /** Trees and tree-building procedures. */ {

/**
 * This class splits a node by a random hyperplane. In order to choose the
 * hyperplane we need to choose the normal to the hyperplane and the position
 * of the hyperplane i.e. the scalar product of the normal and a point.
 *
 * A point will be assigned to the left subtree if the product of
 * this point and the normal is less or equal to the split value (i.e. the
 * position of the hyperplane).
 */
template<typename BoundType, typename MatType = arma::mat>
class RPTreeMaxSplit
{
 public:
  //! The element type held by the matrix type.
  typedef typename MatType::elem_type ElemType;
  //! An information about the partition.
  struct SplitInfo
  {
    //! The normal vector to the hyperplane that splits the node.
    arma::Col<ElemType> direction;
    //! The value according to which the node is being split.
    ElemType splitVal;
  };

  /**
   * Split the node by a random hyperplane.
   *
   * @param bound The bound used for this node.
   * @param data The dataset used by the binary space tree.
   * @param begin Index of the starting point in the dataset that belongs to
   *    this node.
   * @param count Number of points in this node.
   * @param splitInfo An information about the split. This information contains
   *    the direction and the value.
   */
  static bool SplitNode(const BoundType& /*bound*/,
                        MatType& data,
                        const size_t begin,
                        const size_t count,
                        SplitInfo& splitInfo);

  /**
   * Perform the split process according to the information about the
   * split.
   *
   * @param bound The bound used for this node.
   * @param data The dataset used by the binary space tree.
   * @param begin Index of the starting point in the dataset that belongs to
   *    this node.
   * @param count Number of points in this node.
   * @param splitInfo The information about the split.
   */
  static size_t PerformSplit(MatType& data,
                             const size_t begin,
                             const size_t count,
                             const SplitInfo& splitInfo)
  {
    return split::PerformSplit<MatType, RPTreeMaxSplit>(data, begin, count,
        splitInfo);
  }

  /**
   * Perform the split process according to the information about the split and
   * return the list of changed indices.
   *
   * @param bound The bound used for this node.
   * @param data The dataset used by the binary space tree.
   * @param begin Index of the starting point in the dataset that belongs to
   *    this node.
   * @param count Number of points in this node.
   * @param splitInfo The information about the split.
   * @param oldFromNew Vector which will be filled with the old positions for
   *    each new point.
   */
  static size_t PerformSplit(MatType& data,
                             const size_t begin,
                             const size_t count,
                             const SplitInfo& splitInfo,
                             std::vector<size_t>& oldFromNew)
  {
    return split::PerformSplit<MatType, RPTreeMaxSplit>(data, begin, count,
        splitInfo, oldFromNew);
  }

  /**
   * Indicates that a point should be assigned to the left subtree.
   *
   * @param point The point that is being assigned.
   * @param splitInfo An information about the split.
   */
  template<typename VecType>
  static bool AssignToLeftNode(const VecType& point, const SplitInfo& splitInfo)
  {
    return (arma::dot(point, splitInfo.direction) <= splitInfo.splitVal);
  }

 private:
  /**
   * This method finds the position of the hyperplane that will split the node.
   *
   * @param data The dataset used by the binary space tree.
   * @param begin Index of the starting point in the dataset that belongs to
   *    this node.
   * @param count Number of points in this node.
   * @param direction A random vector that is the normal to the hyperplane
   *    which will split the node.
   * @param splitVal The value according which the node will be split.
   */
  static bool GetSplitVal(const MatType& data,
                          const size_t begin,
                          const size_t count,
                          const arma::Col<ElemType>& direction,
                          ElemType& splitVal);
};

} // namespace tree
} // namespace mlpack

// Include implementation.
#include "rp_tree_max_split_impl.hpp"

#endif // MLPACK_CORE_TREE_BINARY_SPACE_TREE_RP_TREE_MAX_SPLIT_HPP
